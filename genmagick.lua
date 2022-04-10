local pf = require('pl.file')
local sorted = require('pl.tablex').sort
local sx = require('pl.stringx')

local wandtypes = {
  Drawing = 'Draw',
  Magick = 'Magick',
  Pixel = 'Pixel',
}

local inttypes = {
  ['unsigned long'] = true,
  ['unsigned long long'] = true,
  ['unsigned short'] = true,
  ['long'] = true,
}

local allfuncs, numtypes = (function()
  local function splitArgs(args)
    local t = {}
    for _, arg in ipairs(sx.split(args, ',')) do
      arg = sx.strip(arg)
      if sx.startswith(arg, 'const ') then
        arg = arg:sub(7)
      end
      table.insert(t, arg)
    end
    return t
  end
  local function parseQualType(ty)
    local ret, args = ty:match('^(.+)%((.*)%)$')
    return {
      ret = sx.strip(ret),
      args = splitArgs(args),
    }
  end
  local t, ns = {}, {}
  local f = io.popen([[
    echo \#include \"wand/MagickWand.h\" |
    clang -Xclang -ast-dump=json -fsyntax-only $(pkg-config ImageMagick --cflags) -xc -
  ]])
  local clang = require('dkjson').use_lpeg().decode(f:read('*a'))
  f:close()
  for _, v in ipairs(clang.inner) do
    if v.kind == 'FunctionDecl' then
      local ty = parseQualType(v.type.qualType)
      if #ty.args >= 1 and sx.endswith(ty.args[1], 'Wand *') then
        local name = ty.args[1]:sub(1, -7)
        assert(wandtypes[name], 'unexpected wand type ' .. name)
        t[v.name] = ty
      end
    elseif v.kind == 'TypedefDecl' and v.type and v.type.qualType then
      local ty = v.type.qualType
      if inttypes[ty] or ns[ty] or sx.startswith(ty, 'enum ') then
        ns[v.name] = true
      end
    end
  end
  return t, ns
end)()

local argCode = {
  ['char *'] = 'const char *arg%d = luaL_checkstring(L, %d);',
  ['unsigned char *'] = 'const char *arg%d = luaL_checkstring(L, %d);',
  ['double'] = 'lua_Number arg%d = luaL_checknumber(L, %d);',
  ['size_t'] = 'lua_Number arg%d = luaL_checknumber(L, %d);',
}

local retCode = {
  ['char *'] = {
    'char *value = FCALL;',
    'lua_pushstring(L, value);',
    'MagickRelinquishMemory(value);',
    'return 1;',
  },
  ['double'] = {
    'lua_pushnumber(L, FCALL);',
    'return 1;',
  },
  ['MagickBooleanType'] = {
    'if (FCALL != MagickTrue) {',
    '  return LOWER_error(L, arg1);',
    '}',
    'lua_pushboolean(L, 1);',
    'return 1;',
  },
  ['size_t'] = {
    'lua_pushnumber(L, FCALL);',
    'return 1;',
  },
  ['void'] = {
    'FCALL;',
    'return 0;',
  },
}

for k in pairs(wandtypes) do
  local pty = k .. 'Wand *'
  argCode[pty] = pty .. 'arg%d = check_' .. k:lower() .. '_wand(L, %d);'
  retCode[pty] = {
    'return wrap_' .. k:lower() .. '_wand(L, FCALL);',
  }
end

for k in pairs(numtypes) do
  argCode[k] = argCode[k] or 'lua_Number arg%d = luaL_checknumber(L, %d);'
  retCode[k] = retCode[k] or {
    'lua_pushnumber(L, FCALL);',
    'return 1;',
  }
end

local skips = {
  ['ChannelFeatures *'] = true,
  ['ChannelStatistics *'] = true,
  ['double *'] = true,
  ['DrawInfo *'] = true,
  ['Image *'] = true,
  ['PixelIterator *'] = true,
  ['PixelView *'] = true,
  ['WandView *'] = true,
}

local function isValid(v)
  for _, arg in ipairs(v.args) do
    if not argCode[arg] then
      return false
    end
  end
  local ret = not not retCode[v.ret]
  local skip = skips[v.ret]
  assert(ret or skip, 'wtf is ' .. v.ret)
  assert(ret ~= skip, 'stale value for ' .. v.ret)
  return ret
end

local wands = {}
for k, v in pairs(wandtypes) do
  wands[k] = {
    funcs = {},
    prefix = v,
  }
end
for k, v in pairs(allfuncs) do
  if isValid(v) then
    local wname = v.args[1]:sub(1, -7)
    if sx.startswith(k, wandtypes[wname]) then
      wands[wname].funcs[k:sub(#wandtypes[wname] + 1)] = {}
    end
  end
end

-- TODO handle these generically
wands.Drawing.funcs.Clear = { name = 'ClearDrawingWand' }
wands.Drawing.funcs.Clone = { name = 'CloneDrawingWand' }
wands.Magick.funcs.GetOptions = {
  special = [[
  MagickWand *wand = check_magick_wand(L, 1);
  const char *pattern = luaL_checkstring(L, 2);
  size_t num_options;
  char **value = MagickGetOptions(wand, pattern, &num_options);
  for (int i = 0; i < num_options; ++i) {
    lua_pushstring(L, value[i]);
    MagickRelinquishMemory(value[i]);
  }
  MagickRelinquishMemory(value);
  return num_options;]],
}
wands.Magick.funcs.ReadImageBlob = {
  special = [[
  MagickWand *wand = check_magick_wand(L, 1);
  size_t length;
  const char *data = luaL_checklstring(L, 2, &length);
  if (MagickReadImageBlob(wand, data, length) != MagickTrue) {
    return magick_error(L, wand);
  }
  lua_pushboolean(L, 1);
  return 1;]],
}

-- TODO find a better way to maintain this blacklist
wands.Magick.funcs.GetOrientationType = nil

local function snake(s)
  -- c/o https://codegolf.stackexchange.com/a/177958
  return s
    :gsub('%f[^%l]%u', '_%1')
    :gsub('%f[^%a]%d', '_%1')
    :gsub('%f[^%d]%a', '_%1')
    :gsub('(%u)(%u%l)', '%1_%2')
    :lower()
end

local function funcbody(name, fname)
  local t = {}
  local wand = wands[name]
  local func = wand.funcs[fname]
  local args = {}
  local cf = allfuncs[func.name or (wand.prefix .. fname)]
  for i, arg in ipairs(cf.args) do
    table.insert(args, 'arg' .. i)
    table.insert(t, argCode[arg]:format(i, i))
  end
  local fcall = ('%s(%s)'):format(func.name or (wand.prefix .. fname), table.concat(args, ', '))
  for _, line in ipairs(retCode[cf.ret]) do
    table.insert(t, (line:gsub('FCALL', fcall):gsub('LOWER', name:lower())))
  end
  return '  ' .. table.concat(t, '\n  ')
end

local plsub = require('pl.template').substitute
pf.write(
  'luamagick.c',
  assert(plsub(
    [[
#include <lauxlib.h>
#include <lua.h>
#include <wand/MagickWand.h>

> for name, wand in sorted(wands) do
static const char $(name:lower())_wand_meta_name[] = "wowrender.magick $(name:lower()) wand";

static int $(name:lower())_error(lua_State *L, $(name)Wand *wand) {
  ExceptionType severity;
  char *error = $(wand.prefix)GetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static $(name)Wand *check_$(name:lower())_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, $(name:lower())_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "$(name:lower()) wand expected");
  return *($(name)Wand **)ud;
}

static int wrap_$(name:lower())_wand(lua_State *L, $(name)Wand *wand) {
  $(name)Wand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, $(name:lower())_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = wand;
  return 1;
}

static int new_$(name:lower())_wand(lua_State *L) {
  return wrap_$(name:lower())_wand(L, New$(name)Wand());
}

> end
> for name, wand in sorted(wands) do
> for fname, func in sorted(wand.funcs) do
static int $(name:lower())_$(snake(fname))(lua_State *L) {
$(func.special or funcbody(name, fname))
}

> end
static struct luaL_Reg $(name:lower())_wand_index[] = {
> for fname in sorted(wand.funcs) do
  {"$(snake(fname))", $(name:lower())_$(snake(fname))},
> end
  {NULL, NULL},
};

> end
static struct luaL_Reg module_index[] = {
> for name in sorted(wands) do
  {"new_$(name:lower())_wand", new_$(name:lower())_wand},
> end
  {NULL, NULL},
};

int luaopen_luamagick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }
> for name in sorted(wands) do
  luaL_newmetatable(L, $(name:lower())_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, $(name:lower())_wand_index);
> end
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  return 1;
}
]],
    {
      _escape = '>',
      funcbody = funcbody,
      sorted = sorted,
      snake = snake,
      wands = wands,
    }
  ))
)
pf.write(
  'README.md',
  assert(plsub(
    [[
# luamagick

A simple mapping of the [ImageMagick](https://imagemagick.org) MagickWand C API to Lua.

## Installation

```sh
luarocks install luamagick
```

## Wand Creation

| C API | Lua API |
| --- | --- |
> for name in sorted(wands) do
| [`New$(name)Wand()`][New$(name)Wand] | `require('luamagick').new_$(name:lower())_wand()` |
> end

> for name, wand in sorted(wands) do
## $(name)Wand

| C API | Lua API |
| --- | --- |
> for k, v in sorted(wand.funcs) do
| `$(v.name or wand.prefix..k)(wand, ...)` | `wand:$(snake(k))(...)` |
> end

> end
> for name in sorted(wands) do
[New$(name)Wand]: https://imagemagick.org/api/$(name:lower())-wand.php#New$(name)Wand
> end
]],
    {
      _escape = '>',
      snake = snake,
      sorted = require('pl.tablex').sort,
      wands = wands,
    }
  ))
)
