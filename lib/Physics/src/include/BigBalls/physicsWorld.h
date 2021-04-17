#pragma once
#include "collisionBody.h"
#include "mathsCommon.h"
#include "physicsDebug.h"
#include "mathsCommon.h"

typedef struct PhysicsWorld {
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int collisionBodyIdCount;
    PVec3 gravity;
    bool debug;
} PhysicsWorld;

/**
 * Initialises a PhysicsWorld object. Gravity is set to a default value of -9.8 (earths gravity).
 * The gravityNormal vector is set to [0,-1,0] by default.
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


//TODO: implement object weights so that force vectors applied to objects can be translated into acceleration
/**
 * Applies a force to a CollisionBody
 * @param physicsWorld the PhysicsWorld the CollisionBody belongs in
 * @param force the force to be applied to the CollisionBody
 * @param xDir the X component of the direction of the force to be applied
 * @param yDir the Y component of the direction of the force to be applied
 * @param zDir the Z component of the direction of the force to be applied
 * @param objID the ID of the CollisionBody
 */
void PhysicsWorld_applyForce(PhysicsWorld *physicsWorld,
                              float force,
                              float xDir,
                              float yDir,
                              float zDir,
                              int objID);

/**
 * Add a game object to the physics engine
 * @param physicsWorld the PhysicsWorld to add a CollisionBody to
 * @param collisionBody the CollisionBody to add to the PhysicsWorld
*/
void PhysicsWorld_addCollisionBody(PhysicsWorld *physicsWorld, CollisionBody *collisionBody);

/**
 * Remove a game object from the physics engine
 * @param physicsWorld The PhysicsWorld to remove a CollisionBody from
 * @param ID The ID of the CollisionBody to be removed
*/
void PhysicsWorld_removeCollisionBody(PhysicsWorld *physicsWorld, int ID);

/**
 * Contains the debug draw functions TODO: UPDATE THIS COMMENT
 * @param physicsWorld the object to draw
 * @param debug the debug object to store the data in
 * @return true if debug has been updated, else false.
 */
bool PhysicsWorld_draw(PhysicsWorld *physicsWorld, DebugData *debug);

/**
 * Toggles debug on or off.
 * @param physicsWorld the physics world to toggle debug
 */
void PhysicsWorld_debugToggle(PhysicsWorld *physicsWorld);

/**
 * Updates the gravity normal for the current physicsWorld. Game engine will calculate the vector and pass in 3
 * floats to ensure compatibility instead of a struct or array.
 * @param physicsWorld the physics world to update
 * @param x coordinate
 * @param y coordinate
 * @param z coordinate
 */
void PhysicsWorld_updateGravityNormal(PhysicsWorld *physicsWorld, float x, float y, float z);

/**
 * Register an object with a collision body for the physics world given.
 * @param physicsWorld physics world to add collision body too.
 * @return a pointer to the collision body that is created. Owned by physics world.
 */
CollisionBody *PhysicsWorld_registerCollisionBody(PhysicsWorld *physicsWorld);