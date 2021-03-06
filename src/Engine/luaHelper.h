#pragma once
#include <lua.h>

/**
 * Initialises Lua to C ABI.
 */
void LuaHelper_init();

/**
 * Load lua script relative to the res/Script file.
 * @param scriptName the name of the script to load.
 */
void LuaHelper_loadScript(const char* scriptName);


/**
 * Add a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_addGameObject(lua_State *L);

/**
 * Set position of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_setPosition(lua_State *L);

/**
 * Get position of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_getPosition(lua_State *L);

/**
 * Set rotation of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_setRotation(lua_State *L);

/**
 * Set the model from lua based of the string of the models file location.
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_setModel(lua_State *L);

/**
 * Get rotation of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int LuaHelper_getRotation(lua_State *L);

int LuaHelper_setCameraPosition(lua_State *L);

int LuaHelper_setCameraYaw(lua_State *L);

int LuaHelper_setCameraPitch(lua_State *L);

int LuaHelper_CameraUpdateView(lua_State *L);