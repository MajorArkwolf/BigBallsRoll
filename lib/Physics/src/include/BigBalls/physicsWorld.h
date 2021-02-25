#pragma once
#include "collisionBody.h"
#include "dynamicArray.h"

//TODO: Temp until vec3 is apart of external library
typedef struct tempVec3 {
    float X;
    float Y;
    float Z;
} tempVec3;

typedef struct PhysicsWorld {
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int collisionBodyIdCount;
    float gravity;
    tempVec3 gravityNormal;
    bool debug;
} PhysicsWorld;

typedef struct DebugDraw {
    size_t numFaces;
    size_t numVertices;
    FloatArray *vertices;
    SizeTArray *faceIndexes;
} DebugDraw;

//TODO: Temp until vec3 is apart of external library
//GravityNormal GravityNormal_init();

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
 */
void PhysicsWorld_draw(PhysicsWorld *physicsWorld, DebugDraw *debug);

/**
 * Initialise the debugDraw object, must be called before using.
 * @param debug the object to initialise
 */
void PhysicsWorld_debugDrawInit(DebugDraw *debug);

/**
 * Frees the contents of a DebugDraw object.
 * @param debug the object to free
 */
void PhysicsWorld_debugDrawFree(DebugDraw *debug);

/**
 * Toggles debug on or off.
 * @param physicsWorld the physics world to toggle debug
 */
void PhysicsWorld_debugToggle(PhysicsWorld *physicsWorld);
