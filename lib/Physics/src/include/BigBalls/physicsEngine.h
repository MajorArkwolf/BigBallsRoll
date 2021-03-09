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

/**
 * TODO: idk if this is in the scope of physics engine, but I imagine the engine must be updated with new data when an object intends to move
 */
bool PhysicsEngine_moveObj(PhysicsEngine *physicsEngine,
             int id,
             float newXOffset,
             float newYOffset,
             float newZOffset);

//TODO: implement object weights so that force vectors applied to objects can be translated into acceleration
bool PhysicsEngine_applyForce(PhysicsEngine *physicsEngine,
                  float force,
                  float xDir,
                  float yDir,
                  float zDir,
                  int objID);

/**
* Add a game object to the physics engine
* @return
*/
int PhysicsEngine_addObj(PhysicsEngine *physicsEngine);

/**
* Remove a game object from the physics engine
* @return
*/
bool PhysicsEngine_removeObj(PhysicsEngine *physicsEngine);
