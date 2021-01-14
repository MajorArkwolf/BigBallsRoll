#pragma once
#include <stdlib.h>
#include <stdbool.h>

/**
 * Initialises the physics world
 */
void physicsWorldInit();

/**
 * Creates a collision body (a collection of colliders dedicated to detecting collisions of an object)
 * @return int ID of the collision body created
 */
size_t createCollisionBody();

/**
 * Destroys a collision body
 * @param ID the ID of the collision body to be destroyed
 * @return bool Success of operation
 */
bool destroyCollisionBody(size_t ID);

/**
 * Creates a box collider in a collision body
 */
void createBoxCollider(size_t ID,
                       size_t xOffset,
                       size_t yOffset,
                       size_t zOffset,
                       size_t xLen,
                       size_t yLen,
                       size_t zLen);

/**
 * Creates a sphere collider in a collision body
 */
void createSphereCollider(size_t ID,
                          size_t xOffset,
                          size_t yOffset,
                          size_t zOffset,
                          size_t radius);

