#include "luaHelper.h"
#include <lualib.h>
#include <lauxlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "Engine/engine.h"

void LuaHelper_loadScript(const char* scriptName) {
    char scriptDir[] = {"res/Script/"};
    //char *lua_location = malloc(sizeof(char) * (strlen(engine.cwd) + strlen(scriptDir) + strlen(scriptName) + 1));
    char *lua_location = calloc((strlen(engine.cwd) + strlen(scriptDir) + strlen(scriptName) + 1), sizeof(char));
    strcpy(lua_location, engine.cwd);
    strcat(lua_location, scriptDir);
    strcat(lua_location, scriptName);
    if (luaL_loadfile(engine.lua, lua_location) != LUA_OK) {
        assert(false);
    }
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    free(lua_location);
}
