#pragma once
#include "Engine/camera.h"
#include "Engine/gameObject.h"

#define MAX_GAME_OBJECTS 10000

typedef int (*fnPtr)();
typedef int (*fnPtrFl)(float);

typedef struct {
    GameObject gameObjects[MAX_GAME_OBJECTS];
    Camera camera;
    size_t NumOfGameObjects;
    fnPtr init;
    fnPtrFl update;
    fnPtrFl draw;
    fnPtr destroy;
} State;

typedef struct {
    State **stack;
    int capacity;
    int top;
} StateManager;

int StateManager_init(StateManager *stateManager);
int StateManager_free(StateManager *stateManager);
int StateManager_push(StateManager *stateManager, State *state);
int StateManager_pop(StateManager *stateManager);
State *StateManager_top(StateManager *stateManager);
int StateManager_update(StateManager *stateManager, float deltaTime);
int StateManager_draw(StateManager *stateManager, float deltaTime);
void State_init(State *state);
