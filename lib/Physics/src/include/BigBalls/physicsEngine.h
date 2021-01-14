#pragma once
#include <stdbool.h>

/**
 * Initialises the physics world
 */
void physicsWorldInit();

/**
 * Creates a collision body (a collection of colliders dedicated to detecting collisions of an object)
 * @return int ID of the collision body created
 */
int createCollisionBody();

/**
 * Destroys a collision body
 * @param ID the ID of the collision body to be destroyed
 * @return bool Success of operation
 */
bool destroyCollisionBody(int ID);

/**
 * Creates a box collider in a collision body
 */
void createBoxCollider(int ID,
                       float xOffset,
                       float yOffset,
                       float zOffset,
                       float xLen,
                       float yLen,
                       float zLen);

/**
 * Creates a sphere collider in a collision body
 */
void createSphereCollider(int ID,
                          float xOffset,
                          float yOffset,
                          float zOffset,
                          float radius);

