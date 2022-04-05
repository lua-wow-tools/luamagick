#include <lauxlib.h>
#include <lua.h>
#include <wand/MagickWand.h>

static const char magick_wand_meta_name[] = "wowrender.magick magick wand";

static int magick_error(lua_State *L, MagickWand *wand) {
  ExceptionType severity;
  char *error = MagickGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static MagickWand *check_magick_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, magick_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "magick wand expected");
  return *(MagickWand **)ud;
}

static int new_magick_wand(lua_State *L) {
  MagickWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, magick_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = NewMagickWand();
  return 1;
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

static int read_image(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *data = luaL_checkstring(L, 2);
  if (MagickReadImage(wand, data) != MagickTrue) {
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

static struct luaL_Reg magick_wand_index[] = {
    {"get_image_format", get_image_format},
    {"get_image_height", get_image_height},
    {"get_image_width", get_image_width},
    {"read_image", read_image},
    {"write_image", write_image},
    {NULL, NULL},
};

static struct luaL_Reg module_index[] = {
    {"new_magick_wand", new_magick_wand},
    {NULL, NULL},
};

int luaopen_wowrender_magick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }
  luaL_newmetatable(L, magick_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, magick_wand_index);
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  return 1;
}
