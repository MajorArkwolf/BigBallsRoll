#pragma once
#include <stdbool.h>
#include "physicsWorld.h"

typedef struct PhysicsEngine{
    PhysicsWorld **physicsWorld;
    size_t numOfPhysicsWorlds;
} PhysicsEngine;

/**
<<<<<<< Updated upstream
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
 * @return a pointer to the new physicsWorld object
 */
PhysicsWorld* PhysicsEngine_newPhysicsWorld(PhysicsEngine *physicsEngine);

/**
 * Frees an existing physicsWorld from the physicsEngine
 * @param physicsEngine contains the physicsWorld to free
 * @param physicsWorld the physicsWorld to free
 */
void PhysicsEngine_freePhysicsWorld(PhysicsEngine *physicsEngine, PhysicsWorld *physicsWorld);

/**
=======
>>>>>>> Stashed changes
 * Creates a collision body (a collection of colliders dedicated to detecting collisions of an object)
 * @param the physics world to add the collision body to
 * @return int ID of the collision body created
 */
int PhysicsEngine_createCollisionBody(PhysicsWorld *physicsWorld);

/**
 * Destroys a collision body
 * @param physicsWorld the physics world the collision body belongs to
 * @param ID the ID of the collision body
 * @return success of operation
 */
bool PhysicsEngine_destroyCollisionBody(PhysicsWorld *physicsWorld, int ID);

/**
 * Checks if two objects are currently colliding with each other
 * TODO: Usage: move objects, check for collision, if collision then calculate new position, else proceed with movement of object
 * @param ID1
 * @param ID2
 * @return
 */
bool PhysicsEngine_checkCollision(PhysicsEngine *physicsEngine,
                    int id1,
                    int id2);

/**
 * TODO: idk if this would be useful or not
 * @param ID1
 * @param newXOffset1
 * @param newYOffset2
 * @param newZOffset3
 * @param ID2
 * @param ID2
 * @return
 */
bool PhysicsEngine_willCollide(PhysicsEngine *physicsEngine,
                 int bodyId1,
                 float newXOffset1,
                 float newYOffset1,
                 float newZOffset1,
                 int bodyId2,
                 float newXOffset2,
                 float newYOffset2,
                 float newZOffset2);

void PhysicsEngine_update(PhysicsEngine *physicsEngine){}