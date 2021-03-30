#include "luaHelper.h"
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Scene/Game/game.h"
#include "Engine/engine.h"
#include "Math/vectorMath.h"

static void print_table(lua_State *L)
{
    if ((lua_type(L, -2) == LUA_TSTRING))
        fprintf(stderr,"%s", lua_tostring(L, -2));

    lua_pushnil(L);
    while(lua_next(L, -2) != 0) {
        if(lua_isstring(L, -1))
            fprintf(stderr, "%s = %s", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
            fprintf(stderr, "%s = %f", lua_tostring(L, -2), lua_tonumber(L, -1));
        else if(lua_istable(L, -1)) {
            print_table(L);
        }
        lua_pop(L, 1);
    }
}

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:  /* strings */
                fprintf(stderr,"`%s'", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                fprintf(stderr,lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                fprintf(stderr,"%g", lua_tonumber(L, i));
                break;

            default:  /* other values */
                fprintf(stderr,"%s", lua_typename(L, t));
                break;

        }
        fprintf(stderr,"  ");  /* put a separator */
    }
    fprintf(stderr,"\n");  /* end the listing */
}

void LuaHelper_loadScript(const char* scriptName) {
    char scriptDir[] = {"res/Script/"};
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

int LuaHelper_addGameObject(lua_State *L) {
    //Get the ID ready for lua to manipulate a game object.
    State *state = StateManager_top(&engine.sM);
    size_t id = state->NumOfGameObjects;
    GameObject_init(&state->gameObjects[id]);
    ++state->NumOfGameObjects;
    lua_pushnumber(L, id);
    return 1;
}

int lua_toggleGameObjectRender(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    bool disableRendering = lua_toboolean(L, 2);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->DisableRendering = disableRendering;
    lua_pop(L, 2);
    return 0;
}

int LuaHelper_setPosition(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->Transform.Position.X = lua_tonumber(L, 2);
    gameObject->Transform.Position.Y = lua_tonumber(L, 3);
    gameObject->Transform.Position.Z = lua_tonumber(L, 4);
    lua_pop(L, 4);
    return 0;
}

int LuaHelper_getPosition(lua_State *L)  {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    lua_pop(L, 1);
    lua_newtable(L);
    lua_pushnumber(L, gameObject->Transform.Position.X);
    lua_setfield(L, 1, "x");
    lua_pushnumber(L, gameObject->Transform.Position.Y);
    lua_setfield(L, 1, "y");
    lua_pushnumber(L, gameObject->Transform.Position.Z);
    lua_setfield(L, 1, "z");
    return 1;
}

int LuaHelper_setRotation(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->Transform.Rotation.X = lua_tonumber(L, 2);
    gameObject->Transform.Rotation.Y = lua_tonumber(L, 3);
    gameObject->Transform.Rotation.Z = lua_tonumber(L, 4);
    lua_pop(L, 4);
    return 0;
}

int LuaHelper_getRotation(lua_State *L)  {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    lua_pop(L, 1);
    lua_newtable(L);
    lua_pushnumber(L, gameObject->Transform.Rotation.X);
    lua_setfield(L, 1, "x");
    lua_pushnumber(L, gameObject->Transform.Rotation.Y);
    lua_setfield(L, 1, "y");
    lua_pushnumber(L, gameObject->Transform.Rotation.Z);
    lua_setfield(L, 1, "z");
    return 1;
}

int LuaHelper_setModel(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    size_t length = 0;
    const char* model = luaL_checklstring(L, 2,  &length);
    gameObject->ModelID = ModelManager_findModel(&engine.modelManager, model);
    lua_pop(L, 2);
    return 0;
}

int LuaHelper_setCameraPosition(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Position.X = lua_tonumber(L, 1);
    StateManager_top(&engine.sM)->camera.Position.Y = lua_tonumber(L, 2);
    StateManager_top(&engine.sM)->camera.Position.Z = lua_tonumber(L, 3);
    lua_pop(L, 3);
    return 0;
}

int LuaHelper_setCameraYaw(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Yaw = lua_tonumber(L, 1);
    lua_pop(L, 1);
    return 0;
}

int LuaHelper_setCameraPitch(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Pitch = lua_tonumber(L, 1);
    lua_pop(L, 1);
    return 0;
}

int LuaHelper_CameraUpdateView(lua_State *L) {
    Camera_updateCameraVectors(&StateManager_top(&engine.sM)->camera);
    return 0;
}

int LuaHelper_CameraLookAt(lua_State *L) {
    float X = lua_tonumber(L, 1);
    float Y = lua_tonumber(L, 2);
    float Z = lua_tonumber(L, 3);
    Camera_lookAtObject(&StateManager_top(&engine.sM)->camera, X, Y, Z);
    return 0;
}

int LuaHelper_GameNextLevel(lua_State *L) {
    Game_NextLevel(StateManager_top(&engine.sM));
    return 0;
}

int LuaHelper_NormaliseVec3(lua_State *L) {
    Vec3 vec3;
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "x");
        vec3.X = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        vec3.Y = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        vec3.Z = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 1);

        vec3 = VectorMath_normaliseVec3(&vec3);

        lua_newtable(L);
        lua_pushnumber(L, vec3.X);
        lua_setfield(L, 1, "x");
        lua_pushnumber(L, vec3.Y);
        lua_setfield(L, 1, "y");
        lua_pushnumber(L, vec3.Z);
        lua_setfield(L, 1, "z");
        return 1;
    }
    return 0;
}

int LuaHelper_CrossProductVec3(lua_State *L) {
    Vec3 firstVec3, secondVec3, result;
    if (lua_istable(L, -1) && lua_istable(L, -2)) {
        lua_getfield(L, -1, "x");
        firstVec3.X = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        firstVec3.Y = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        firstVec3.Z = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 1);
        firstVec3 = VectorMath_normaliseVec3(&firstVec3);

        lua_getfield(L, -1, "x");
        secondVec3.X = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        secondVec3.Y = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        secondVec3.Z = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 1);
        secondVec3 = VectorMath_normaliseVec3(&secondVec3);

        result = VectorMath_crossProductVec3ByVec3(&firstVec3, &secondVec3);

        lua_newtable(L);
        lua_pushnumber(L, result.X);
        lua_setfield(L, 1, "x");
        lua_pushnumber(L, result.Y);
        lua_setfield(L, 1, "y");
        lua_pushnumber(L, result.Z);
        lua_setfield(L, 1, "z");
        return 1;
    }
    return 0;

}

void LuaHelper_init() {
    //Register functions for lua.
    // Math
    lua_pushcfunction(engine.lua, LuaHelper_NormaliseVec3);
    lua_setglobal(engine.lua, "NormaliseVec");
    lua_pushcfunction(engine.lua, LuaHelper_CrossProductVec3);
    lua_setglobal(engine.lua, "CrossProductVec");

    //Game Objects
    lua_pushcfunction(engine.lua, LuaHelper_addGameObject);
    lua_setglobal(engine.lua, "GameObjectRegister");
    lua_pushcfunction(engine.lua, LuaHelper_setPosition);
    lua_setglobal(engine.lua, "GameObjectSetPosition");
    lua_pushcfunction(engine.lua, LuaHelper_getPosition);
    lua_setglobal(engine.lua, "GameObjectGetPosition");
    lua_pushcfunction(engine.lua, LuaHelper_setRotation);
    lua_setglobal(engine.lua, "GameObjectSetRotation");
    lua_pushcfunction(engine.lua, LuaHelper_getRotation);
    lua_setglobal(engine.lua, "GameObjectGetRotation");
    lua_pushcfunction(engine.lua, LuaHelper_setModel);
    lua_setglobal(engine.lua, "GameObjectSetModel");
    lua_pushcfunction(engine.lua, lua_toggleGameObjectRender);
    lua_setglobal(engine.lua, "GameObjectToggleRender");

    // Camera
    lua_pushcfunction(engine.lua, LuaHelper_setCameraPosition);
    lua_setglobal(engine.lua, "CameraSetPosition");
    lua_pushcfunction(engine.lua, LuaHelper_setCameraYaw);
    lua_setglobal(engine.lua, "CameraSetYaw");
    lua_pushcfunction(engine.lua, LuaHelper_setCameraPitch);
    lua_setglobal(engine.lua, "CameraSetPitch");
    lua_pushcfunction(engine.lua, LuaHelper_CameraUpdateView);
    lua_setglobal(engine.lua, "CameraUpdateView");
    lua_pushcfunction(engine.lua, LuaHelper_CameraLookAt);
    lua_setglobal(engine.lua, "CameraLookAt");

    // Scene
    lua_pushcfunction(engine.lua, LuaHelper_GameNextLevel);
    lua_setglobal(engine.lua, "GameNextLevel");

    lua_pushnumber(engine.lua, engine.seed);
    lua_setglobal(engine.lua, "seed");
    lua_getglobal(engine.lua, "Init");
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
}
