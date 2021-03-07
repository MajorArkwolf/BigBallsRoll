#include "luaHelper.h"
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Scene/Game/game.h"
#include "Engine/engine.h"

void LuaHelper_init() {
    //Register functions for lua.

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
    lua_pushcfunction(engine.lua, LuaHelper_setCameraPosition);
    lua_setglobal(engine.lua, "CameraSetPosition");
    lua_pushcfunction(engine.lua, LuaHelper_setCameraYaw);

    // Camera
    lua_setglobal(engine.lua, "CameraSetYaw");
    lua_pushcfunction(engine.lua, LuaHelper_setCameraPitch);
    lua_setglobal(engine.lua, "CameraSetPitch");
    lua_pushcfunction(engine.lua, LuaHelper_CameraUpdateView);
    lua_setglobal(engine.lua, "CameraUpdateView");
    lua_pushcfunction(engine.lua, LuaHelper_CameraLookAt);
    lua_setglobal(engine.lua, "CameraLookAt");

    // Scene
    lua_setglobal(engine.lua, "GameNextLevel");
    lua_pushcfunction(engine.lua, LuaHelper_GameNextLevel);


    lua_pushnumber(engine.lua, engine.seed);
    lua_setglobal(engine.lua, "seed");
    lua_getglobal(engine.lua, "Init");
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
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

int LuaHelper_setPosition(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->Transform.Position.X = lua_tonumber(L, 2);
    gameObject->Transform.Position.Y = lua_tonumber(L, 3);
    gameObject->Transform.Position.Z = lua_tonumber(L, 4);

    return 0;
}

int LuaHelper_getPosition(lua_State *L)  {
    lua_newtable(L);
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    lua_pushnumber(L, gameObject->Transform.Position.X);
    lua_rawseti(L,-2,1);
    lua_pushnumber(L, gameObject->Transform.Position.Y);
    lua_rawseti(L,-2,2);
    lua_pushnumber(L, gameObject->Transform.Position.Z);
    lua_rawseti(L,-2,3);
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

    return 0;
}

int LuaHelper_getRotation(lua_State *L)  {
    lua_newtable(L);
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    lua_pushnumber(L, gameObject->Transform.Rotation.X);
    lua_rawseti(L,-2,1);
    lua_pushnumber(L, gameObject->Transform.Rotation.Y);
    lua_rawseti(L,-2,2);
    lua_pushnumber(L, gameObject->Transform.Rotation.Z);
    lua_rawseti(L,-2,3);
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

    return 0;
}

int LuaHelper_setCameraPosition(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Position.X = lua_tonumber(L, 1);
    StateManager_top(&engine.sM)->camera.Position.Y = lua_tonumber(L, 2);
    StateManager_top(&engine.sM)->camera.Position.Z = lua_tonumber(L, 3);

    return 0;
}

int LuaHelper_setCameraYaw(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Yaw = lua_tonumber(L, 1);
    return 0;
}

int LuaHelper_setCameraPitch(lua_State *L) {
    StateManager_top(&engine.sM)->camera.Pitch = lua_tonumber(L, 1);
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