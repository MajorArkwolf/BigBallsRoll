#include "stateManager.h"
#include <stdlib.h>
#include <stdbool.h>

int StateManager_scale(StateManager *stateManager) {
    stateManager->capacity *= 2;
    stateManager->stack = realloc(stateManager->stack, stateManager->capacity * sizeof(State *));
    return stateManager->capacity;
}

int StateManager_init(StateManager *stateManager) {
    stateManager->capacity = 3;
    stateManager->stack = calloc(stateManager->capacity, sizeof(State *));
    stateManager->top = -1;
    return 0;
}

int StateManager_free(StateManager *stateManager) {
    do {
        StateManager_pop(stateManager);
    } while (stateManager->top > -1);
    free(stateManager->stack);
    return 0;
}

int StateManager_push(StateManager *stateManager, State *state) {
    if (stateManager->top + 1 == stateManager->capacity) {
        StateManager_scale(stateManager);
    }
    ++stateManager->top;
    stateManager->stack[stateManager->top] = state;
    if (state->init != NULL) { state->init(); }
    return stateManager->top;
}

int StateManager_pop(StateManager *stateManager) {
    if (stateManager->top == -1) return 0;
    State *top = StateManager_top(stateManager);
    if (top->destroy != NULL) top->destroy();
    stateManager->stack[stateManager->top] = NULL;
    stateManager->top--;
    return stateManager->top;
}

State *StateManager_top(StateManager *stateManager) {
    return stateManager->stack[stateManager->top];
}

int StateManager_update(StateManager *stateManager, float deltaTime) {
    State *state = StateManager_top(stateManager);
    if (state->update != NULL) {
        return state->update(deltaTime);
    }
    return 1;
}

int StateManager_draw(StateManager *stateManager, float deltaTime) {
    State *state = StateManager_top(stateManager);
    if (state->draw != NULL) {
        return state->draw(deltaTime);
    }
    return 1;
}

void State_init(State *state) {
    state->NumOfGameObjects = 0;
    state->draw = NULL;
    state->update = NULL;
    state->destroy = NULL;
    state->init = NULL;
    state->camera = Camera_construct();
}
