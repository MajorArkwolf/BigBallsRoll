#include "stateManager.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int StateManager_scale(StateManager *stateManager) {
    stateManager->capacity *= 2;
    stateManager->stack = realloc(stateManager->stack, stateManager->capacity * sizeof(State *));
    if (stateManager->stack == NULL) {
        assert(false);
        return 1;
    }
    return stateManager->capacity;
}

int StateManager_init(StateManager *stateManager) {
    stateManager->capacity = 3;
    stateManager->stack = calloc(stateManager->capacity, sizeof(State *));
    if (stateManager->stack == NULL) {
        assert(false);
        return 1;
    }
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

int StateManager_keyDown(StateManager *stateManager, InputType inputType) {
    State *state = StateManager_top(stateManager);
    if (state->keyDown != NULL) {
        return state->keyDown(inputType);
    }
    return 1;
}

int StateManager_keyUp(StateManager *stateManager, InputType inputType) {
    State *state = StateManager_top(stateManager);
    if (state->keyUp != NULL) {
        return state->keyUp(inputType);
    }
    return 1;
}

int StateManager_mouseMove(StateManager *stateManager, float x, float y) {
    State *state = StateManager_top(stateManager);
    if (state->mouseMovement != NULL) {
        return state->mouseMovement(x, y);
    }
    return 1;
}

void State_init(State *state) {
    state->NumOfGameObjects = 0;
    state->draw = NULL;
    state->update = NULL;
    state->destroy = NULL;
    state->init = NULL;
    state->keyDown = NULL;
    state->keyUp = NULL;
    state->mouseMovement = NULL;
    state->camera = Camera_construct();
}
