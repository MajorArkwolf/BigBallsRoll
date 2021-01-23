#pragma once
#include "Engine/stateManager.h"
#include <lua.h>

/**
 * Main Menu Init, takes a Generic State struct and sets it up for use in the main menu.
 * @param state a generic state struct, should be instantiated but not contain information as it will be overwritten.
 */
void Game_init(State *state);


int Game_addGameObject(lua_State *L);

int Game_setPosition(lua_State *L);

int Game_setRotation(lua_State *L);

int Game_setModel(lua_State *L);