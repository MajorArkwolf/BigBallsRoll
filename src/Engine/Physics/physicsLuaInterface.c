#include "physicsLuaInterface.h"
#include <BigBalls/physicsEngine.h>
#include "Engine/engine.h"
#include <lualib.h>
#include <lauxlib.h>

CollisionBody* PhysicsLuaInterface_GetCollisionBody(size_t id) {
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    return PhysicsWorld_findCollisionBody(StateManager_top(&engine.sM)->physicsWorld, gameObject->physicsCollisionID);
}

int PhysicsLuaInterface_registerCollisionBody(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->physicsCollisionID = PhysicsEngine_addObj(&engine.physicsEngine);
    return 0;
}

int PhysicsLuaInterface_setOffsetPosition(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    CollisionBody *cb = PhysicsLuaInterface_GetCollisionBody(id);
    if (cb != NULL) {
        int X = lua_tonumber(L, 2);
        int Y = lua_tonumber(L, 3);
        int Z = lua_tonumber(L, 4);
        CollisionBody_setPos(cb, X, Y, Z);
    }
    lua_pop(L, 4);
    return 0;
}

int PhysicsLuaInterface_AddAABBCollider(lua_State *L) {
    return 0;
}

int PhysicsLuaInterface_AddSphereCollider(lua_State *L) {
    return 0;
}

void PhysicsLuaInterface_init() {
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_registerCollisionBody);
    lua_setglobal(engine.lua, "PhysicsRegisterCollisionBody");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_setOffsetPosition);
    lua_setglobal(engine.lua, "PhysicsSetOffsetPosition");

    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
}