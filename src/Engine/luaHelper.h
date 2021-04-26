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
 * Updates the lua player config values.
 */
void LuaHelper_PlayerConfig();
