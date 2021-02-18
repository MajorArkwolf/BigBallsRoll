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
 * Adds a CollisionBody to a PhysicsWorld
 * @param physicsWorld The target PhysicsWorld
 * @param collisionBody The CollisionBOdy to be added
 */
void PhysicsWorld_addCollisionBody(PhysicsWorld *physicsWorld, CollisionBody *collisionBody);

/**
 * Removes a CollisionBody from a PhysicsWorld via its ID
 * @param physicsWorld The target PhysicsWorld
 * @param id The ID of the CollisionBody to be removed
 */
void PhysicsWorld_removeCollisionBody(PhysicsWorld *physicsWorld, int id);

/**
 * Creates a collision body (a collection of colliders dedicated to detecting collisions of an object)
 * @param the physics world to add the collision body to
 * @return int ID of the collision body created
 */
int PhysicsWorld_createCollisionBody(PhysicsWorld *physicsWorld);

/**
 * Destroys a collision body
 * @param physicsWorld the physics world the collision body belongs to
 * @param ID the ID of the collision body
 * @return success of operation
 */
bool PhysicsWorld_destroyCollisionBody(PhysicsWorld *physicsWorld, int ID);

/**
 * Updates a Object
 * @param physicsWorld The physics world containing the object to be updated
 * @param objId The ID of the object ot be updated
 * @return success or failure of operation
 */
bool PhysicsWorld_updateObj(PhysicsWorld *physicsWorld, int objId);
