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
    float xPos; // give position so collider positions are relative to collisionBody position
    float yPos;
    float zPos;
    float xRot; // give rotation so collider rotations are relative to collisionbody rotation
    float yRot;
    float zRot;
} CollisionBody;

/**
 * Initialise collisionBody
 * @param collisionBody
 */
void CollisionBody_init(CollisionBody *collisionBody);

/**
 * Free collisionBody
 * @param collisionBody
 */
void CollisionBody_free(CollisionBody *collisionBody);

/**
 * A heap array was chosen for its ability to be resized, at the cost of performance when being resized (when colliders are added or destroyed).
 * As object creation/destruction are not speed-critical operations in our project this tradeoff seems acceptable
 * (the alternative being two static arrays per collisonBody (for each type) which seemed a bit excessive)
 * @param colliderManager
 * @param boxCollider
 */
void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                    BoxCollider *boxCollider);

/**
 * Remove a boxcollider from a collisionbody
 * @param collisionBody
 * @param id
 */
void CollisionBody_rmBoxCollider(CollisionBody *collisionBody,
                                   int id);

/**
 * Add a spherecollider to a collisionbody
 * @param collisionBody
 * @param sphereCollider
 */
void CollisionBody_addSphereCollider(CollisionBody *collisionBody,
                                       SphereCollider *sphereCollider);

/**
 * Remove a spherecollider from a collisionbody (by ID)
 * @param collisionBody
 * @param id
 */
void CollisionBody_rmSphereCollider(CollisionBody *collisionBody,
                                      int id);

/**
 * Translate a collisonbody (and therefore all of its member colliders)
 * @param collisionBody
 * @param xDist
 * @param yDist
 * @param zDist
 */
void CollisionBody_translate(CollisionBody *collisionBody,
                             float xDist,
                             float yDist,
                             float zDist);

/**
 * Rotate a collisionbody (and therefore all of its member colliders)
 * @param collisionBody
 * @param xRot
 * @param yRot
 * @param zRot
 */
void CollisionBody_rotate(CollisionBody *collisionBody,
                          float xRot,
                          float yRot,
                          float zRot);

/**
 * Scale a collisionbody uniformly (and therefore all of its member colliders)
 * @param collisionBody
 * @param scaleFactor
 */
void CollisionBody_scale(CollisionBody *collisionBody, float scaleFactor);
