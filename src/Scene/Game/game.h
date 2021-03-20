#pragma once
#include "Engine/stateManager.h"
#include <lua.h>

/**
 * Game Init, takes a Generic State struct and sets it up for use in the main menu.
 * @param state a generic state struct, should be instantiated but not contain information as it will be overwritten.
 */
void Game_init(State *state);

/**
 * Resets the world ready for the next level.
 * @param state Reset all state related information.
 */
void Game_NextLevel(State *state);
