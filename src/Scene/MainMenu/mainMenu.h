#pragma once
#include "Engine/stateManager.h"
#include "Engine/textureManager.h"

/**
 * Main Menu Init, takes a Generic State struct and sets it up for use in the main menu.
 * @param state a generic state struct, should be instantiated but not contain information as it will be overwritten.
 */
void MainMenu_init(State *state);
