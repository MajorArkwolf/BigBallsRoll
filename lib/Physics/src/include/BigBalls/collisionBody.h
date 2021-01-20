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
 * A stack array was chosen for its ability to be resized, at the cost of performance when being resized (when colliders are added or destroyed). As object creation/destruction are not speed-critical operations in our project this tradeoff seems acceptable (the alternative being two static arrays per collisonBody (for each type) which seemed a bit excessive)
 * @param colliderManager
 * @param boxCollider
 */
void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                    BoxCollider *boxCollider);

void CollisionBody_rmBoxCollider(CollisionBody *collisionBody,
                                   int id);

void CollisionBody_addSphereCollider(CollisionBody *collisionBody,
                                       SphereCollider *sphereCollider);

void CollisionBody_rmSphereCollider(CollisionBody *collisionBody,
                                      int id);