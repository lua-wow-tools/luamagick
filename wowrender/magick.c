#include <lauxlib.h>
#include <lua.h>
#include <wand/MagickWand.h>

static const char drawing_wand_meta_name[] = "wowrender.magick drawing wand";
static const char magick_wand_meta_name[] = "wowrender.magick magick wand";

static int magick_error(lua_State *L, MagickWand *wand) {
  ExceptionType severity;
  char *error = MagickGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static DrawingWand *check_drawing_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, drawing_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "drawing wand expected");
  return *(DrawingWand **)ud;
}

static MagickWand *check_magick_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, magick_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "magick wand expected");
  return *(MagickWand **)ud;
}

static int new_drawing_wand(lua_State *L) {
  DrawingWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, drawing_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = NewDrawingWand();
  return 1;
}

static int new_magick_wand(lua_State *L) {
  MagickWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, magick_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = NewMagickWand();
  return 1;
}

static int draw_annotation(lua_State *L) {
  DrawingWand *wand = check_drawing_wand(L, 1);
  lua_Number x = luaL_checknumber(L, 2);
  lua_Number y = luaL_checknumber(L, 3);
  const char *text = luaL_checkstring(L, 4);
  DrawAnnotation(wand, x, y, text);
}

static int draw_image(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  DrawingWand *drawing_wand = check_drawing_wand(L, 2);
  MagickDrawImage(wand, drawing_wand);
}

static int get_image_format(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  char *format = MagickGetImageFormat(wand);
  lua_pushstring(L, format);
  MagickRelinquishMemory(format);
  return 1;
}

static int get_image_height(lua_State *L) {
  lua_pushnumber(L, MagickGetImageHeight(check_magick_wand(L, 1)));
  return 1;
}

static int get_image_width(lua_State *L) {
  lua_pushnumber(L, MagickGetImageWidth(check_magick_wand(L, 1)));
  return 1;
}

static int get_number_images(lua_State *L) {
  lua_pushnumber(L, MagickGetNumberImages(check_magick_wand(L, 1)));
  return 1;
}

static int get_option(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *key = luaL_checkstring(L, 2);
  char *value = MagickGetOption(wand, key);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int get_options(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *pattern = luaL_checkstring(L, 2);
  size_t num_options;
  char **value = MagickGetOptions(wand, pattern, &num_options);
  for (int i = 0; i < num_options; ++i) {
    lua_pushstring(L, value[i]);
    MagickRelinquishMemory(value[i]);
  }
  MagickRelinquishMemory(value);
  return num_options;
}

static int read_image(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *data = luaL_checkstring(L, 2);
  if (MagickReadImage(wand, data) != MagickTrue) {
    return magick_error(L, wand);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int set_option(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *key = luaL_checkstring(L, 2);
  const char *value = luaL_checkstring(L, 3);
  if (MagickSetOption(wand, key, value) != MagickTrue) {
    return magick_error(L, wand);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int write_image(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *path = luaL_checkstring(L, 2);
  if (MagickWriteImage(wand, path) != MagickTrue) {
    return magick_error(L, wand);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static struct luaL_Reg drawing_wand_index[] = {
    {"draw_annotation", draw_annotation},
    {NULL, NULL},
};

static struct luaL_Reg magick_wand_index[] = {
    {"draw_image", draw_image},
    {"get_image_format", get_image_format},
    {"get_image_height", get_image_height},
    {"get_image_width", get_image_width},
    {"get_number_images", get_number_images},
    {"get_option", get_option},
    {"get_options", get_options},
    {"read_image", read_image},
    {"set_option", set_option},
    {"write_image", write_image},
    {NULL, NULL},
};

static struct luaL_Reg module_index[] = {
    {"new_drawing_wand", new_drawing_wand},
    {"new_magick_wand", new_magick_wand},
    {NULL, NULL},
};

int luaopen_wowrender_magick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }
  luaL_newmetatable(L, drawing_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, drawing_wand_index);
  luaL_newmetatable(L, magick_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, magick_wand_index);
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  return 1;
}
