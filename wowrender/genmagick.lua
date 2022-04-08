local sx = require('pl.stringx')

local allfuncs = (function()
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
    local ret, args = ty:match('^(.+)%((.+)%)$')
    return {
      ret = sx.strip(ret),
      args = splitArgs(args),
    }
  end
  local t = {}
  local f = io.popen([[
    echo \#include \"wand/MagickWand.h\" |
    clang -Xclang -ast-dump=json -fsyntax-only $(pkg-config ImageMagick --cflags) -xc -
  ]])
  local clang = require('dkjson').use_lpeg().decode(f:read('*a'))
  f:close()
  for _, v in ipairs(clang.inner) do
    if v.kind == 'FunctionDecl' then
      local ty = v.type.qualType
      if ty:match('DrawingWand') or ty:match('MagickWand') or ty:match('PixelWand') then
        t[v.name] = parseQualType(ty)
      end
    end
  end
  return t
end)()

local wands = {
  Drawing = {
    prefix = 'Draw',
    funcs = {
      Clear = {
        name = 'ClearDrawingWand',
      },
      Clone = {
        name = 'CloneDrawingWand',
      },
    },
  },
  Magick = {
    prefix = 'Magick',
    funcs = {
      GetOptions = {
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
      },
    },
  },
  Pixel = {
    prefix = 'Pixel',
    funcs = {},
  },
}

local validArgs = {
  ['char *'] = true,
  ['unsigned char *'] = true,
  ['double'] = true,
  ['DrawingWand *'] = true,
  ['size_t'] = true,
}

local validRets = {
  ['char *'] = true,
  ['double'] = true,
  ['DrawingWand *'] = true,
  ['MagickBooleanType'] = true,
  ['size_t'] = true,
  ['void'] = true,
}

local function isValid(v)
  for i = 2, #v.args do
    if not validArgs[v.args[i]] then
      return false
    end
  end
  return validRets[v.ret]
end

for k, v in pairs(allfuncs) do
  if sx.startswith(k, 'Draw') and v.args[1] == 'DrawingWand *' and isValid(v) then
    wands.Drawing.funcs[k:sub(5)] = {}
  elseif sx.startswith(k, 'Magick') and v.args[1] == 'MagickWand *' and isValid(v) then
    wands.Magick.funcs[k:sub(7)] = {}
  elseif sx.startswith(k, 'Pixel') and v.args[1] == 'PixelWand *' and isValid(v) then
    wands.Pixel.funcs[k:sub(6)] = {}
  end
end

local function snake(s)
  -- c/o https://codegolf.stackexchange.com/a/177958
  return s
    :gsub('%f[^%l]%u', '_%1')
    :gsub('%f[^%a]%d', '_%1')
    :gsub('%f[^%d]%a', '_%1')
    :gsub('(%u)(%u%l)', '%1_%2')
    :lower()
end

local t = {
  '#include <lauxlib.h>',
  '#include <lua.h>',
  '#include <wand/MagickWand.h>',
  '',
}

local w = {}
for name in pairs(wands) do
  table.insert(w, name)
end
table.sort(w)
for _, name in ipairs(w) do
  local wand = wands[name]
  local fmts = {
    LOWER = name:lower(),
    PREFIX = wand.prefix,
    WAND = name,
  }
  local function add(s)
    for k, v in pairs(fmts) do
      s = s:gsub(k, v)
    end
    table.insert(t, s)
  end
  add([[
static const char LOWER_wand_meta_name[] = "wowrender.magick LOWER wand";

static int LOWER_error(lua_State *L, WANDWand *wand) {
  ExceptionType severity;
  char *error = PREFIXGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static WANDWand *check_LOWER_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, LOWER_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "LOWER wand expected");
  return *(WANDWand **)ud;
}

static int wrap_LOWER_wand(lua_State *L, WANDWand *wand) {
  WANDWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, LOWER_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = wand;
  return 1;
}

static int new_LOWER_wand(lua_State *L) {
  return wrap_LOWER_wand(L, NewWANDWand());
}
]])

  local fs = {}
  for fname in pairs(wand.funcs) do
    table.insert(fs, fname)
  end
  table.sort(fs)
  for _, fname in ipairs(fs) do
    local func = wand.funcs[fname]
    fmts.SNAKE = snake(fname)
    add('static int LOWER_SNAKE(lua_State *L) {')
    if func.special then
      table.insert(t, func.special)
    else
      add('  WANDWand *wand = check_LOWER_wand(L, 1);')
      local args = { 'wand' }
      local cf = allfuncs[func.name or (wand.prefix .. fname)]
      for ai = 2, #cf.args do
        local arg = cf.args[ai]
        table.insert(args, 'arg' .. ai)
        if arg == 'double' or arg == 'size_t' then
          add(('  lua_Number arg%d = luaL_checknumber(L, %d);'):format(ai, ai))
        elseif arg == 'char *' or arg == 'unsigned char *' then
          add(('  const char *arg%d = luaL_checkstring(L, %d);'):format(ai, ai))
        elseif arg == 'DrawingWand *' then
          add(('  DrawingWand *arg%d = check_drawing_wand(L, %d);'):format(ai, ai))
        else
          error('invalid func arg ' .. arg)
        end
      end
      fmts.FCALL = ('%s(%s)'):format(func.name or (wand.prefix .. fname), table.concat(args, ', '))
      if cf.ret == 'double' or cf.ret == 'size_t' then
        add('  lua_pushnumber(L, FCALL);')
        add('  return 1;')
      elseif cf.ret == 'char *' then
        add('  char *value = FCALL;')
        add('  lua_pushstring(L, value);')
        add('  MagickRelinquishMemory(value);')
        add('  return 1;')
      elseif cf.ret == 'MagickBooleanType' then
        add('  if (FCALL != MagickTrue) {')
        add('    return LOWER_error(L, wand);')
        add('  }')
        add('  lua_pushboolean(L, 1);')
        add('  return 1;')
      elseif cf.ret == 'DrawingWand *' then
        add('  return wrap_LOWER_wand(L, FCALL);')
      elseif cf.ret == 'void' then
        add('  FCALL;')
        add('  return 0;')
      else
        error('invalid func.returns ' .. cf.ret)
      end
    end
    add('}')
    add('')
  end
  add('static struct luaL_Reg LOWER_wand_index[] = {')
  for _, fname in ipairs(fs) do
    fmts.SNAKE = snake(fname)
    add('  {"SNAKE", LOWER_SNAKE},')
  end
  add('  {NULL, NULL},')
  add('};')
  add('')
end
table.insert(t, 'static struct luaL_Reg module_index[] = {')
for _, name in ipairs(w) do
  local s = name:lower()
  table.insert(t, ('  {"new_%s_wand", new_%s_wand},'):format(s, s))
end
table.insert(
  t,
  [[
  {NULL, NULL},
};

int luaopen_wowrender_magick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }]]
)

for _, name in ipairs(w) do
  table.insert(
    t,
    (([[
  luaL_newmetatable(L, LOWER_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, LOWER_wand_index);
]]):gsub('LOWER', name:lower()))
  )
end

table.insert(
  t,
  [[
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  return 1;
}
]]
)

local f = io.open('wowrender/magick.c', 'w')
f:write(table.concat(t, '\n'))
f:close()
