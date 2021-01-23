#pragma once
#include <lua.h>

/**
 * Load lua script relative to the res/Script file.
 * @param scriptName the name of the script to load.
 */
void LuaHelper_loadScript(const char* scriptName);