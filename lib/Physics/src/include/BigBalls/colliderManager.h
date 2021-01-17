#pragma once
#include <stdlib.h>
#include "boxCollider.h"
#include "sphereCollider.h"

typedef struct ColliderManager{
    // implementation of stack
    BoxCollider **BoxColliders;
    size_t numOfBoxColliders;
    SphereCollider **SphereColliders;
    size_t numOfSphereColliders;
    size_t numOfColliders; // TODO: may be redundant
    int idCount;
} ColliderManager;

void ColliderManager_init(ColliderManager *colliderManager);

void ColliderManager_free(ColliderManager *colliderManager);

/**
 * A stack array was chosen for its ability to be resized, at the cost of performance when being resized (when colliders are added or destroyed). As object creation/destruction are not speed-critical operations in our project this tradeoff seems acceptable (the alternative being two static arrays per collisonBody (for each type) which seemed a bit excessive)
 * @param colliderManager
 * @param boxCollider
 */
void ColliderManager_addBoxCollider(ColliderManager *colliderManager,
                                     BoxCollider *boxCollider);

void ColliderManager_rmBoxCollider(ColliderManager *colliderManager,
                                    int id);

void ColliderManager_addSphereCollider(ColliderManager *colliderManager,
                                        SphereCollider *sphereCollider);

void ColliderManager_rmSphereCollider(ColliderManager *colliderManager,
                                       int id);