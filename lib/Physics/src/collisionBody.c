#include "include/BigBalls/collisionBody.h"
#include <assert.h>

int getID(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    // increment and return new id
    return collisionBody->idCount++;
}

void CollisionBody_init(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    collisionBody->numOfColliders = 0;
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->BoxColliders = NULL;
    collisionBody->SphereColliders = NULL;
    collisionBody->idCount = 0;
    collisionBody->id = -1; //TODO: request id here or not?
}

void CollisionBody_free(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    // Free stack-allocated box colliders
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        free(collisionBody->BoxColliders[i]);
    }
    // Free stack-allocated sphere colliders
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        free(collisionBody->SphereColliders[i]);
    }
    // Reset colliderManager values
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->numOfColliders = 0;
}

void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                  BoxCollider *boxCollider){
    // Allocate new, larger array
    if(collisionBody->BoxColliders == NULL){
        collisionBody->BoxColliders = calloc(1, sizeof(BoxCollider));
    }
    else{
        collisionBody->BoxColliders = realloc(collisionBody->BoxColliders, sizeof(BoxCollider) * collisionBody->numOfBoxColliders + 1);
    }
    // Copy BoxCollider object into array
    collisionBody->BoxColliders[collisionBody->numOfBoxColliders] = boxCollider;
    // Assign ID to BoxCollider
    collisionBody->BoxColliders[collisionBody->numOfBoxColliders]->id = getID(collisionBody);
    collisionBody->numOfBoxColliders++;
    collisionBody->numOfColliders++;
}

void CollisionBody_rmBoxCollider(CollisionBody *collisionBody,
                                   int id){
    if(collisionBody->numOfBoxColliders - 1 != 0){
        // Allocate memory for smaller array
        BoxCollider **newBoxColliders = calloc(collisionBody->numOfBoxColliders - 1, sizeof(BoxCollider));
        // Only copy elements that are not to be removed
        for(size_t i = 0; i < collisionBody->numOfBoxColliders - 1; ++i){
            if(collisionBody->BoxColliders[i]->id != id){
                newBoxColliders[i] = collisionBody->BoxColliders[i];
            }
        }
        // free old array
        free(collisionBody->BoxColliders);
        // assign new array to colliderManager
        collisionBody->BoxColliders = newBoxColliders;
    }
    else{
        // if size = 0, store null pointer
        free(collisionBody->BoxColliders);
        collisionBody->BoxColliders = NULL;
    }
}

void CollisionBody_addSphereCollider(CollisionBody *collisionBody,
                                       SphereCollider *sphereCollider){
    // Allocate new, larger array
    if(collisionBody->SphereColliders == NULL){
        collisionBody->SphereColliders = calloc(1, sizeof(SphereCollider));
    }
    else{
        collisionBody->SphereColliders = realloc(collisionBody->SphereColliders, sizeof(SphereCollider) * collisionBody->numOfSphereColliders + 1);
    }
    // Copy SphereCollider object into array
    collisionBody->SphereColliders[collisionBody->numOfSphereColliders] = sphereCollider;
    // Assign ID to BoxCollider
    collisionBody->SphereColliders[collisionBody->numOfSphereColliders]->id = getID(collisionBody);
    collisionBody->numOfSphereColliders++;
    collisionBody->numOfColliders++;
}

void CollisionBody_rmSphereCollider(CollisionBody *collisionBody,
                                      int id){
    if(collisionBody->numOfSphereColliders - 1 != 0){
        // Allocate memory for smaller array
        SphereCollider **newSphereColliders = calloc(collisionBody->numOfSphereColliders - 1, sizeof(SphereCollider));
        // Only copy elements that are not to be removed
        for(size_t i = 0; i < collisionBody->numOfSphereColliders - 1; ++i){
            if(collisionBody->SphereColliders[i]->id != id){
                newSphereColliders[i] = collisionBody->SphereColliders[i];
            }
        }
        // free old array
        free(collisionBody->SphereColliders);
        // assign new array to colliderManager
        collisionBody->SphereColliders = newSphereColliders;
    }
    else{
        // if size = 0, store null pointer
        free(collisionBody->SphereColliders);
        collisionBody->SphereColliders = NULL;
    }
}