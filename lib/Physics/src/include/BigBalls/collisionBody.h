#pragma once
#include <stdlib.h>
#include "boxCollider.h"
#include "sphereCollider.h"
#include "mathsCommon.h"
#include "stdbool.h"

typedef struct CollisionBody{
    // implementation of stack
    BoxCollider **BoxColliders;
    size_t numOfBoxColliders;
    SphereCollider **SphereColliders;
    size_t numOfSphereColliders;
    size_t numOfColliders; // TODO: may be redundant
    int id;
    float xPos; // give position so collider positions are relative to CollisionBody position
    float yPos;
    float zPos;
    float xRot; // give rotation so collider rotations are relative to CollisionBody rotation
    float yRot;
    float zRot;
    PVec3 velocity;
    PVec3 force;
    float mass; // physical mass of CollisionBody
    float AABBx1; // two coordinates required for AABB
    float AABBy1;
    float AABBz1;
    float AABBx2;
    float AABBy2;
    float AABBz2;
    float restitution; // << Bounciness, this possibly should be added to individual colliders.
    bool isStatic;
} CollisionBody;

// struct to wrap array to make it easy to pass in and out of functions, and keep data on the stack for performance benefits
typedef struct BoxColliderVerts{
    Matrix41 verts[8];
} BoxColliderVerts;

/**
 * Initialise collisionBody
 * @param collisionBody The CollisionBody object to initialise
 */
void CollisionBody_init(CollisionBody *collisionBody);

/**
 * Free collisionBody
 * @param collisionBody The CollisionBody object to free
 */
void CollisionBody_free(CollisionBody *collisionBody);

/**
 * Adds a BoxCollider to a CollisionBody
 * A heap array was chosen for its ability to be resized, at the cost of performance when being resized (when colliders are added or destroyed).
 * As object creation/destruction are not speed-critical operations in our project this tradeoff seems acceptable
 * (the alternative being two static arrays per CollisionBody (for each type) which seemed a bit excessive)
 * @param collisionBody The CollisionBody object to add a BoxCollider object to
 * @param boxCollider The BoxCollider object to be added to the CollisionBody
 */
void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                    BoxCollider *boxCollider);

/**
 * Add a SphereCollider to a CollisionBody
 * @param collisionBody The CollisionBody object to add a SphereCollider object to
 * @param sphereCollider The SphereCollider object to be added to the CollisionBody
 */
void CollisionBody_addSphereCollider(CollisionBody *collisionBody,
                                       SphereCollider *sphereCollider);

/**
 * Translate a CollisionBody (and therefore all of its member colliders)
 * @param collisionBody The CollisionBody to be translated
 * @param xDist The x-delta the CollisionBody should be moved by
 * @param yDist The y-delta the CollisionBody should be moved by
 * @param zDist The z-delta the CollisionBody should be moved by
 */
void CollisionBody_translate(CollisionBody *collisionBody,
                             float xDist,
                             float yDist,
                             float zDist);

/**
 * Rotate a CollisionBody (and therefore all of its member colliders)
 * @param collisionBody The CollisionBody to be rotated
 * @param xRot The x-delta the CollisionBody should be rotated by
 * @param yRot The y-delta the CollisionBody should be rotated by
 * @param zRot The z-delta the CollisionBody should be rotated by
 */
void CollisionBody_rotate(CollisionBody *collisionBody,
                          float xRot,
                          float yRot,
                          float zRot);

/**
 * Scale a CollisionBody uniformly (and therefore all of its member colliders)
 * @param collisionBody The CollisionBody to be uniformly scaled
 * @param scaleFactor The scale factor the CollisionBody should be scaled by
 * (scale factor of 1 would have no change, 0.5 would be half size, 2 would be double size)
 */
void CollisionBody_scale(CollisionBody *collisionBody, float scaleFactor);

/**
 * Stops a CollisionBody from being considered by collision detection, and stops all forces from moving it (including gravity)
 * Maintains the current velocity of the object
 * @param collisionBody The CollisionBody to put to sleep
 * TODO: implement
 */
void CollisionBody_sleep(CollisionBody *collisionBody);

/**
 * Allows forces to act on a CollisionBody and for the body to be involved in collisions after being in a sleep state
 * @param collisionBody The CollisionBody to stop sleeping
 */
void CollisionBody_awake(CollisionBody *collisionBody);

/**
 * Stops movement and removes forces from CollisionBody
 * @param collisionBody The CollisionBody to be stopped
 */
void CollisionBody_stop(CollisionBody *collisionBody);

/**
 * Updates the AABB of the CollisionBody
 * @param collisionBody the CollisionBody that should have its AABB updated
 */
void CollisionBody_updateAABB(CollisionBody *collisionBody);

// TODO: Stub
/**
 * Updates the OOBB of the CollisionBody
 * @param collisionBody The CollisionBody that should have its OOBB updated
 */
void CollisionBody_updateOOBB(CollisionBody *collisionBody);

/**
 * Sets the position of the CollisionBody
 * This moves all colliders relative to this point
 * @param collisionBody The CollisionBody that should have its position set
 * @param x The x parameter of the destination coordinate
 * @param y The y parameter of the destination coordinate
 * @param z The z parameter of the destination coordinate
 */
void CollisionBody_setPos(CollisionBody *collisionBody,
                            float x,
                            float y,
                            float z);

/**
 * Sets the rotation of the CollisionBody
 * This rotates all colliders relative to this rotation
 * @param collisionBody The CollisionBody that should have its rotation set
 * @param x The x parameter of the target rotation
 * @param y The y parameter of the target rotation
 * @param z The z parameter of the target rotation
 */
void CollisionBody_setRot(CollisionBody *collisionBody,
                            float x,
                            float y,
                            float z);

/**
 * Register a box collider from an external program
 * @param cb A registered collision body in a physics world
 * @param offsetPosition Offset position of size 3 (X, Y, Z) relative to the collision body origin.
 * @param length extrusion of the box of size 3 (X, Y, Z)
 */
void CollisionBody_registerBoxCollider(CollisionBody *cb,
                                       const float *offsetPosition,
                                       const float *length);

/**
 * Register a box collider from an external program
 * @param cb A registered collision body in a physics world
 * @param offsetPosition Offset position of size 3 (X, Y, Z) relative to the collision body origin.
 * @param radius the radius of the sphere to create.
 */
void CollisionBody_registerSphereCollider(CollisionBody *cb,
                                          const float *offsetPosition,
                                          float radius);

/**
 * Set a collision body to become static, a static object will not move and if
 * two static bodies are colliding they will be ignored.
 * @param cb collision body to alter
 * @param isStatic true if static, false if not
 */
void CollisionBody_setCollisionBodyStatic(CollisionBody *cb, bool isStatic);

/**
 * Add force onto an existing body, this will sum all existing forces and will reset after resolution.
 * @param cb collision body to update
 * @param xForce force in the x direction
 * @param yForce force in the y direction
 * @param zForce force in the z direction
 */
void CollisionBody_addForce(CollisionBody *cb, float xForce, float yForce, float zForce);

/**
 * Reset the force of a collision body to zero.
 * @param cb collision body whose force to reset
 */
void CollisionBody_resetForce(CollisionBody *cb);
