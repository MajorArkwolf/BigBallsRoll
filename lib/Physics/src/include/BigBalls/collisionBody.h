#pragma once

#include <stdlib.h>
#include "boxCollider.h"
#include "sphereCollider.h"

typedef struct CollisionBody{
    // implementation of stack
    BoxCollider **BoxColliders;
    size_t numOfBoxColliders;
    SphereCollider **SphereColliders;
    size_t numOfSphereColliders;
    size_t numOfColliders; // TODO: may be redundant
    int idCount;
    int id;
    float xPos; // give position so collider positions are relative to CollisionBody position
    float yPos;
    float zPos;
    float xRot; // give rotation so collider rotations are relative to CollisionBody rotation
    float yRot;
    float zRot;
    float xVel; // current velocity of CollisionBody (as a vector)
    float yVel;
    float zVel;
    float mass; // physical mass of CollisionBody
} CollisionBody;

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
