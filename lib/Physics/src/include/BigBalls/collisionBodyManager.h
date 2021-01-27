#pragma once

#include "collisionBody.h"

typedef struct CollisionBodyManager{
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int idCount;
} CollisionBodyManager;

/**
 * Initialises a CollisionBodyManager object
 * @param collisionBodyManager The CollisionBodyManager to be initialised
 */
void CollisionBodyManager_init(CollisionBodyManager *collisionBodyManager);

/**
 * Frees a CollisionBodyManager from memory
 * @param collisionBodyManager The CollisionBodyManager to be freed
 */
void CollisionBodyManager_free(CollisionBodyManager *collisionBodyManager);

/**
 * Adds a CollisionBody to a CollisionBodyManager
 * @param collisionBodyManager The target CollisionBodyManager
 * @param collisionBody The CollisionBOdy to be added
 */
void CollisionBodyManager_add(CollisionBodyManager *collisionBodyManager,
                              CollisionBody *collisionBody);

/**
 * Removes a CollisionBody from a CollisionBodyManager via its ID
 * @param collisionBodyManager The target CollisionBodyManager
 * @param id The ID of the CollisionBody to be removed
 */
void CollisionBodyManager_rm(CollisionBodyManager *collisionBodyManager,
                             int id);
