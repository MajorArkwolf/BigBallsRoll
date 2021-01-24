#pragma once
#include "Engine/stateManager.h"
#include <lua.h>

/**
 * Main Menu Init, takes a Generic State struct and sets it up for use in the main menu.
 * @param state a generic state struct, should be instantiated but not contain information as it will be overwritten.
 */
void Game_init(State *state);

/**
 * Add a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int Game_addGameObject(lua_State *L);

/**
 * Set position of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int Game_setPosition(lua_State *L);

/**
 * Set rotation of a game object from LUA
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int Game_setRotation(lua_State *L);

/**
 * Set the model from lua based of the string of the models file location.
 * @param L lua's state to get the information from LUA
 * @return how many parameters are returned
 */
int Game_setModel(lua_State *L);
