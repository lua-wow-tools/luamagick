local wands = {
  Drawing = {
    prefix = 'Draw',
    funcs = {
      Annotation = {
        args = { 'number', 'number', 'string' },
      },
      Clear = {
        name = 'ClearDrawingWand',
      },
    },
  },
  Magick = {
    prefix = 'Magick',
    funcs = {
      DrawImage = {
        args = { 'DrawingWand' },
        returns = 'bool',
      },
      GetImageFormat = {
        returns = 'string',
      },
      GetImageHeight = {
        returns = 'number',
      },
      GetImageWidth = {
        returns = 'number',
      },
      GetNumberImages = {
        returns = 'number',
      },
      GetOption = {
        args = { 'string' },
        returns = 'string',
      },
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
      ReadImage = {
        args = { 'string' },
        returns = 'bool',
      },
      SetOption = {
        args = { 'string', 'string' },
        returns = 'bool',
      },
      WriteImage = {
        args = { 'string' },
        returns = 'bool',
      },
    },
  },
}

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

static int new_LOWER_wand(lua_State *L) {
  WANDWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, LOWER_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = NewWANDWand();
  return 1;
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
    add('static int SNAKE(lua_State *L) {')
    if func.special then
      table.insert(t, func.special)
    else
      add('  WANDWand *wand = check_LOWER_wand(L, 1);')
      local args = { 'wand' }
      for i, arg in ipairs(func.args or {}) do
        local ai = i + 1
        table.insert(args, 'arg' .. ai)
        if arg == 'number' then
          add(('  lua_Number arg%d = luaL_checknumber(L, %d);'):format(ai, ai))
        elseif arg == 'string' then
          add(('  const char *arg%d = luaL_checkstring(L, %d);'):format(ai, ai))
        elseif arg == 'DrawingWand' then
          add(('  DrawingWand *arg%d = check_drawing_wand(L, %d);'):format(ai, ai))
        else
          error('invalid func arg ' .. arg)
        end
      end
      fmts.FCALL = ('%s(%s)'):format(func.name or (wand.prefix .. fname), table.concat(args, ', '))
      if func.returns == 'number' then
        add('  lua_pushnumber(L, FCALL);')
        add('  return 1;')
      elseif func.returns == 'string' then
        add('  char *value = FCALL;')
        add('  lua_pushstring(L, value);')
        add('  MagickRelinquishMemory(value);')
        add('  return 1;')
      elseif func.returns == 'bool' then
        add('  if (FCALL != MagickTrue) {')
        add('    return LOWER_error(L, wand);')
        add('  }')
        add('  lua_pushboolean(L, 1);')
        add('  return 1;')
      elseif func.returns == nil then
        add('  FCALL;')
        add('  return 0;')
      else
        error('invalid func.returns ' .. func.returns)
      end
    end
    add('}')
    add('')
  end
  add('static struct luaL_Reg LOWER_wand_index[] = {')
  for _, fname in ipairs(fs) do
    local s = snake(fname)
    add(('  {"%s", %s},'):format(s, s))
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
