#pragma once
#include <stdbool.h>
#include "physicsWorld.h"

typedef struct PhysicsEngine{
    PhysicsWorld *physicsWorld;
} PhysicsEngine;

/**
 * Initialises the physics world
 */
void PE_newPhysicsWorld(PhysicsEngine *physicsEngine);

/**
 * Creates a collision body (a collection of colliders dedicated to detecting collisions of an object)
 * @return int ID of the collision body created
 */
int PE_createCollisionBody(PhysicsEngine *physicsEngine);

/**
 * Destroys a collision body
 * @param ID the ID of the collision body to be destroyed
 * @return bool Success of operation
 */
bool PE_destroyCollisionBody(PhysicsEngine *physicsEngine,
                          int id);

/**
 * Checks if two objects are currently colliding with each other
 * TODO: Usage: move objects, check for collision, if collision then calculate new position, else proceed with movement of object
 * @param ID1
 * @param ID2
 * @return
 */
bool PE_checkCollision(PhysicsEngine *physicsEngine,
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
bool PE_willCollide(PhysicsEngine *physicsEngine,
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
bool PE_moveObj(PhysicsEngine *physicsEngine,
             int id,
             float newXOffset,
             float newYOffset,
             float newZOffset);

//TODO: implement object weights so that force vectors applied to objects can be translated into acceleration
bool PE_applyForce(PhysicsEngine *physicsEngine,
                  float force,
                  float xDir,
                  float yDir,
                  float zDir,
                  int objID);

/**
* Add a game object to the physics engine
* @return
*/
int PE_addObj(PhysicsEngine *physicsEngine);

/**
* Remove a game object from the physics engine
* @return
*/
bool PE_removeObj(PhysicsEngine *physicsEngine);

bool PE_updateObj(PhysicsEngine *physicsEngine,
               int objId);

void PE_draw(PhysicsEngine *physicsEngine);
