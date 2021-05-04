#include "physicsLuaInterface.h"
#include <BigBalls/physicsEngine.h>
#include "Engine/engine.h"
#include <lualib.h>
#include <lauxlib.h>
#include <stdbool.h>

int PhysicsLuaInterface_registerCollisionBody(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    PhysicsWorld *pw = StateManager_top(&engine.sM)->physicsWorld;
    gameObject->collisionBody = PhysicsWorld_registerCollisionBody(pw);
    return 0;
}

int PhysicsLuaInterface_setPosition(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    if (gameObject->collisionBody != NULL) {
        float X = lua_tonumber(L, 2);
        float Y = lua_tonumber(L, 3);
        float Z = lua_tonumber(L, 4);
        CollisionBody_setPos(gameObject->collisionBody, X, Y, Z);
    }
    lua_pop(L, 4);
    return 0;
}

int PhysicsLuaInterface_setRotation(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    if (gameObject->collisionBody != NULL) {
        float X = lua_tonumber(L, 2);
        float Y = lua_tonumber(L, 3);
        float Z = lua_tonumber(L, 4);
        CollisionBody_setRot(gameObject->collisionBody, X, Y, Z);
    }
    lua_pop(L, 4);
    return 0;
}


//make object static
int PhysicsLuaInterface_setCollisionBodyStatic(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    if (gameObject->collisionBody != NULL) {
        bool isStatic = lua_toboolean(L, 2);
        CollisionBody_setCollisionBodyStatic(gameObject->collisionBody, isStatic);
    }
    return 0;
}

//sleep object

//delete collision body

int PhysicsLuaInterface_AddAABBCollider(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    if (gameObject->collisionBody != NULL) {
        float pos[3];
        float len[3];

        lua_getfield(L, -1, "x");
        len[0] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        len[1] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        len[2] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "x");
        pos[0] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        pos[1] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        pos[2] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 2);

        CollisionBody_registerBoxCollider(gameObject->collisionBody, pos, len);
    }
    return 0;
}

int PhysicsLuaInterface_AddSphereCollider(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    if (gameObject->collisionBody != NULL) {
        float pos[3];
        float radius = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "x");
        pos[0] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "y");
        pos[1] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "z");
        pos[2] = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_pop(L, 2);
        CollisionBody_registerSphereCollider(gameObject->collisionBody, pos, radius);
    }
    return 0;
}

int PhysicsLuaInterface_resetPhysicsWorld(lua_State *L) {
    PhysicsEngine *pe = &engine.physicsEngine;
    PhysicsWorld *pw = StateManager_top(&engine.sM)->physicsWorld;
    PhysicsEngine_freePhysicsWorld(pe, pw);
    pw = PhysicsEngine_newPhysicsWorld(pe);
    StateManager_top(&engine.sM)->physicsWorld = pw;
    return 0;
}

void PhysicsLuaInterface_init() {
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_registerCollisionBody);
    lua_setglobal(engine.lua, "PhysicsRegisterCollisionBody");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_setPosition);
    lua_setglobal(engine.lua, "PhysicsSetPosition");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_AddAABBCollider);
    lua_setglobal(engine.lua, "PhysicsAddAABBCollider");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_AddSphereCollider);
    lua_setglobal(engine.lua, "PhysicsAddSphereCollider");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_resetPhysicsWorld);
    lua_setglobal(engine.lua, "PhysicsWorldReset");
    lua_pushcfunction(engine.lua, PhysicsLuaInterface_setCollisionBodyStatic);
    lua_setglobal(engine.lua, "PhysicsCollisionBodySetStatic");
}
