#pragma once
#include <stdlib.h>
#include "Math/transform.h"

/// GameObject Structure
typedef struct GameObject {
    Transform Transform;
    size_t ModelID;
    char *Name;
} GameObject;

/**
 * Initialise a game object, the object must already be allocated before it can be initialised.
 * @param gameObject to be initialised
 */
void GameObject_init(GameObject *gameObject);

/**
 * Frees a game object. Note, this will not free the object itself, rather it will free any contents inside of it that are heap allocated.
 * @param gameObject
 */
void GameObject_free(GameObject *gameObject);

/**
 * This will draw a game object based of its model, this is a primitive rendering solution and should only be used for prototyping.
 * @param gameObject game object to be drawn.
 */
void GameObject_draw(GameObject *gameObject);
