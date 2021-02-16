#pragma once

#include "collisionBody.h"

//TODO: Temp until vec3 is apart of external library
typedef struct GravityNormal {
    float X;
    float Y;
    float Z;
} GravityNormal;

typedef struct PhysicsWorld{
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int collisionBodyIdCount;
    float gravity;
    GravityNormal gravityNormal;
} PhysicsWorld;

//TODO: Temp until vec3 is apart of external library
GravityNormal GravityNormal_init();

//TODO: stub, not sure how this will work atm.
void PhysicsWorld_updateGravityNormal(float x, float y, float z);

/**
 * Searches for a CollisionBody by ID in a PhysicsWorld
 * Returns NULL if match is not found
 * @param physicsWorld The PhysicsWorld to search for the CollisionBody in
 * @param ID The ID of the CollisionBody to find
 * @return CollisionBody* CollisionBody pointer of found CollisionBody, or NULL if not found
 */
CollisionBody* PhysicsWorld_findCollisionBody(PhysicsWorld *physicsWorld, int ID);

/**
 * Initialises a PhysicsWorld object
 * @param physicsWorld The PhysicsWorld to be initialised
 */
void PhysicsWorld_init(PhysicsWorld *physicsWorld);

/**
 * Frees a PhysicsWorld from memory
 * @param physicsWorld The PhysicsWorld to be freed
 */
void PhysicsWorld_free(PhysicsWorld *physicsWorld);

/**
 * Returns a collision body ID and increments collisionBodyIdCount by one
 * @param physicsWorld the physics world containing the new collision body
 * @return the ID
 */
int PhysicsWorld_newCollisionBodyID(PhysicsWorld *physicsWorld);

/**
 * Updates the position and rotation data of objects in the PhysicsWorld based on time passed since last update,
 * current forces on objects and current velocities, detecting and resolving collisions where appropriate
 * @param physicsWorld
 * @param deltaTime
 */
void PhysicsWorld_update(PhysicsWorld *physicsWorld, float deltaTime);

//TODO: implement object weights so that force vectors applied to objects can be translated into acceleration
bool PhysicsEngine_applyForce(PhysicsWorld *physicsWorld,
                              const float force,
                              const float xDir,
                              const float yDir,
                              const float zDir,
                              const int objID);

/**
* Add a game object to the physics engine
* @return int The id of the added object
*/
int PhysicsEngine_addCollisionBody(PhysicsWorld *physicsWorld);

/**
* Remove a game object from the physics engine
* @return
*/
bool PhysicsEngine_removeCollisionBody(PhysicsWorld *physicsWorld, const int ID);
