#pragma once
#include <stdlib.h>
#include "Math/transform.h"

typedef struct GameObject {
    char *Name;
    size_t ModelID;
    Transform Transform;
} GameObject;

void GameObject_init(GameObject *gameObject);

void GameObject_free(GameObject *gameObject);

void GameObject_draw(GameObject *gameObject);
