#include "gameObject.h"
#include <stdlib.h>

void GameObject_init(GameObject *gameObject) {
    gameObject->Name = NULL;
    gameObject->ModelID = 0;
    gameObject->Transform = Transformation_construct();
}

void GameObject_free(GameObject *gameObject) {
    free(gameObject->Name);
    GameObject_init(gameObject);
}