#pragma once

#include "collisionBody.h"

typedef struct CollisionBodyManager{
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int idCount;
} CollisionBodyManager;

/**
 * Searches for a CollisionBody by ID in a CollisionBodyManager
 * Returns NULL if match is not found
 * @param collisionBodyManager The CollisionBodyManager to search for the CollisionBody in
 * @param ID The ID of the CollisionBody to find
 * @return CollisionBody* CollisionBody pointer of found CollisionBody, or NULL if not found
 */
CollisionBody* findCollisionBody(CollisionBodyManager *collisionBodyManager, int ID);

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
