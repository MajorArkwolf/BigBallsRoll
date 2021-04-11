#pragma once
#include <stdbool.h>
#include "physicsWorld.h"

typedef struct PhysicsEngine{
    PhysicsWorld **physicsWorld;
    size_t numOfPhysicsWorlds;
} PhysicsEngine;

/**
 * Initialize Physics Engine
 * @param physicsEngine the object to be initialized
 */
void PhysicsEngine_init(PhysicsEngine *physicsEngine);

/**
 * Frees the physicsWorlds associated with this physicsEngine
 * @param physicsEngine the object to free
 */
void PhysicsEngine_free(PhysicsEngine *physicsEngine);

/**
 * Calls PhysicsWorld_init and creates a new PhysicsWorld
 * Can be used to replace existing physicsWorld with a new one
 * @param physicsEngine The object containing the physicsWorld object
 * @return PhysicsWorld a pointer to the new physicsWorld object
 */
PhysicsWorld* PhysicsEngine_newPhysicsWorld(PhysicsEngine *physicsEngine);

/**
 * Frees an existing physicsWorld from the physicsEngine
 * @param physicsEngine contains the physicsWorld to free
 * @param physicsWorld the physicsWorld to free
 */
void PhysicsEngine_freePhysicsWorld(PhysicsEngine *physicsEngine, PhysicsWorld *physicsWorld);
