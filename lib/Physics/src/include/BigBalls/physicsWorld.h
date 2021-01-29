#pragma once

#include "collisionBody.h"

//Temp until vec3 is apart of external library
typedef struct GravityNormal {
    float X;
    float Y;
    float Z;
} GravityNormal;

typedef struct PhysicsWorld{
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int idCount;
    float gravity;
    GravityNormal gravityNormal;
} PhysicsWorld;

//Temp until vec3 is apart of external library
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
CollisionBody* findCollisionBody(PhysicsWorld *physicsWorld, int ID);

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
void PhysicsWorld_addCollisionBody(PhysicsWorld *physicsWorld,
                              CollisionBody *collisionBody);

/**
 * Removes a CollisionBody from a PhysicsWorld via its ID
 * @param physicsWorld The target PhysicsWorld
 * @param id The ID of the CollisionBody to be removed
 */
void PhysicsWorld_removeCollisonBody(PhysicsWorld *physicsWorld,
                             int id);
