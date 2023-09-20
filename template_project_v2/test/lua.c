
#include "utest.h"
#include "minilua.h"

UTEST(lua, adds_1_2)
{
    lua_State *L = luaL_newstate();

    luaL_dostring(L, "return 1 + 2");
    int result = lua_tonumber(L, -1);
    lua_pop(L, 1);
    lua_close(L);

    ASSERT_EQ(3, result);
}
