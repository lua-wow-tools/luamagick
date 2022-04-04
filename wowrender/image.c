#include <lua.h>
#include <lauxlib.h>

static struct luaL_Reg wowrender_image[] = {
  {NULL, NULL}
};

int luaopen_wowrender_image(lua_State *L) {
  lua_newtable(L);
  luaL_register(L, NULL, wowrender_image);
  return 1;
}
