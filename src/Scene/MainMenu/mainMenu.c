#include "mainMenu.h"
#include <stdlib.h>
#include <main.h>

int draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&sM)->gameObjects[index]);
    }
    return 0;
}

void MainMenu_init(State *state) {
    state->camera = Camera_construct();
    state->update = NULL;
    state->draw = draw;

    //Test Model Load
    GameObject_init(&state->gameObjects[0]);
    state->gameObjects[0].ModelID = ModelManager_findModel(&modelManager, "Off/colourcube.off");
    state->NumOfGameObjects = 1;
}