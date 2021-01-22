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
    collisionBody->xPos = 0;
    collisionBody->yPos = 0;
    collisionBody->zPos = 0;
    collisionBody->xRot = 0;
    collisionBody->yRot = 0;
    collisionBody->zRot = 0;
}

void CollisionBody_free(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    free(collisionBody->BoxColliders);
    free(collisionBody->SphereColliders);
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
        for(size_t i = 0; i < collisionBody->numOfBoxColliders - 1; ++i){
            if(collisionBody->BoxColliders[i]->id != id){
                // doesn't actually remove the data from memory for performance reasons
                // O(n-1) vs O(n-x) time to copy all data but desired ID to new array
                // Only a small struct of primitives so memory efficiency is less pertinent of an issue
                collisionBody->BoxColliders[i] = NULL;
            }
        }
    }
    else{
        // if size = 0, free whole array and store null pointer
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
        for(size_t i = 0; i < collisionBody->numOfSphereColliders - 1; ++i){
            if(collisionBody->SphereColliders[i]->id != id){
                // doesn't actually remove the data from memory for performance reasons
                // O(n-1) vs O(n-x) time to copy all data but desired ID to new array
                // Only a small struct of primitives so memory efficiency is less pertinent of an issue
                collisionBody->SphereColliders[i] = NULL;
            }
        }
    }
    else{
        // if size = 0, store null pointer
        free(collisionBody->SphereColliders);
        collisionBody->SphereColliders = NULL;
    }
}
