#pragma once

#include "Engine/camera.h"
#include "Engine/GameObjects/gameObject.h"
#include "Engine/InputManager.h"
#include <BigBalls/physicsEngine.h>

#define MAX_GAME_OBJECTS 1000000

/// Simple typedefs to distinguish between a function pointer and a function pointer that takes a float as a parameter
typedef int (*fnPtr)();

typedef int (*fnPtrFl)(float);

typedef int (*fnPtrInput)(InputType);

typedef int (*fnPtrDblDbl)(double, double);

typedef int (*fnPtrIntInt)(int, int);

/// State Structure
typedef struct State {
    GameObject gameObjects[MAX_GAME_OBJECTS];
    Camera camera;
    size_t NumOfGameObjects;
    size_t registeredLightIDs;
    PhysicsWorld* physicsWorld;
    fnPtr init;
    fnPtrFl update;
    fnPtrFl draw;
    fnPtr destroy;
    fnPtrInput keyDown;
    fnPtrInput keyUp;
    fnPtrDblDbl mouseMovement;
    fnPtrIntInt mouseKeys;
    bool endStateSafely;
    bool isStatePaused;
    bool skyboxDraw;
} State;

/// A Stack implementation that holds a stack of states
typedef struct {
    State **stack;
    int capacity;
    int top;
} StateManager;

/**
 * Initialises the Stack manager, must be freed before calling on an existing State Manager
 * @param stateManager State Manager to initialise.
 * @return 0 on success or 1 on failure
 */
int StateManager_init(StateManager *stateManager);

/**
 * Frees the entire stack.
 * @param stateManager State Manager to free
 * @return 0 on success and 1 on failure
 */
int StateManager_free(StateManager *stateManager);

/**
 * Push a new state onto the stack
 * @param stateManager State Manager to push onto
 * @param state State to be added, Ownership is transferred to the state manager and the lifetime of the state must exceed that of the State Manager for memory safety.
 * @return 0 on success and 1 on failure
 */
int StateManager_push(StateManager *stateManager, State *state);

/**
 * Pop the top state off the stack
 * @param stateManager State Manager to pop off, the state is freed and set to NULL
 * @return  0 on success and 1 on failure
 */
int StateManager_pop(StateManager *stateManager);

/**
 * Get the top element on the stack
 * @param stateManager The state manager we want to point too
 * @return the current top state on the stack
 */
State *StateManager_top(StateManager *stateManager);

/**
 * Calls the function pointer for update on the top of the stack
 * @param stateManager state manager to check the stack of
 * @param deltaTime delta time since last update, important to have
 * @return 0 on success and 1 on failure
 */
int StateManager_update(StateManager *stateManager, float deltaTime);

/**
 * Calls the function pointer for draw on the top of the stack
 * @param stateManager state manager to check the stack of
 * @param deltaTime delta time since last update, not important in a draw call
 * @return 0 on success and 1 on failure
 */
int StateManager_draw(StateManager *stateManager, float deltaTime);

/**
 * Key down function to pass key presses into our game state
 * @param stateManager state manager to check the stack of
 * @param inputType the input pressed by the user
 * @return 0 on success and 1 on failure
 */
int StateManager_keyDown(StateManager *stateManager, InputType inputType);

/**
 * Key Up function to pass key presses into our game state
 * @param stateManager state manager to check the stack of
 * @param inputType the input pressed by the user
 * @return 0 on success and 1 on failure
 */
int StateManager_keyUp(StateManager *stateManager, InputType inputType);

/**
 * Passes the difference in mouse movement into our scene.
 * @param stateManager state manager to check the stack of
 * @param x the difference in x pos
 * @param y the difference in y pos
 * @return 0 on success and 1 on failure
 */
int StateManager_mouseMove(StateManager *stateManager, double x, double y);

/**
 * Passes the mouse button state to the game
 * @param stateManager state manager to check the stack of
 * @param button the button id being pressed
 * @param buttonState if the button is pressed or released
 * @return
 */
int StateManager_mouseKeys(StateManager *stateManager, int button, int buttonState);

/**
 * Checks to see if the state has requested it to end and will safely remove itself
 * at the end of the loop to ensure nothing is referencing it before it terminates.
 * @param stateManager the current active state manager.
 */
void StateManager_safeStateRemoval(StateManager *stateManager);

/**
 * Initialises a base state for use
 * @param state State to initialise, must be allocated prior to being passed in
 */
void State_init(State *state);

/**
 * Register a new light
 * @param state Current game state
 * @return return an ID between 1 and the max opengl lights possible, 0 is an error.
 */
size_t State_registerLight(State *state);

/**
 * Deregister all lights in a given scene
 * @param state the state to deregister lights from
 */
void State_deregisterLights(State *state);
