#include "include/BigBalls/colliderManager.h"
#include <assert.h>

int getID(ColliderManager *colliderManager){
    assert(colliderManager != NULL);
    // increment and return new id
    return colliderManager->idCount++;
}

void ColliderManager_init(ColliderManager *colliderManager){
    assert(colliderManager != NULL);
    colliderManager->numOfColliders = 0;
    colliderManager->numOfBoxColliders = 0;
    colliderManager->numOfSphereColliders = 0;
    colliderManager->BoxColliders = NULL;
    colliderManager->SphereColliders = NULL;
    colliderManager->idCount = 0;
}

void ColliderManager_free(ColliderManager *colliderManager){
    assert(colliderManager != NULL);
    // Free stack-allocated box colliders
    for(size_t i = 0; i < colliderManager->numOfBoxColliders; ++i){
        free(colliderManager->BoxColliders[i]);
    }
    // Free stack-allocated sphere colliders
    for(size_t i = 0; i < colliderManager->numOfSphereColliders; ++i){
        free(colliderManager->SphereColliders[i]);
    }
    // Reset colliderManager values
    colliderManager->numOfBoxColliders = 0;
    colliderManager->numOfSphereColliders = 0;
    colliderManager->numOfColliders = 0;
}

void ColliderManager_addBoxCollider(ColliderManager *colliderManager,
                          BoxCollider *boxCollider){
    // Allocate new, larger array
    if(colliderManager->BoxColliders == NULL){
        colliderManager->BoxColliders = calloc(1, sizeof(BoxCollider));
    }
    else{
        colliderManager->BoxColliders = realloc(colliderManager->BoxColliders, sizeof(BoxCollider) * colliderManager->numOfBoxColliders + 1);
    }
    // Copy BoxCollider object into array
    colliderManager->BoxColliders[colliderManager->numOfBoxColliders] = boxCollider;
    // Assign ID to BoxCollider
    colliderManager->BoxColliders[colliderManager->numOfBoxColliders]->ID = getID(colliderManager);
    colliderManager->numOfBoxColliders++;
    colliderManager->numOfColliders++;
}

void ColliderManager_rmBoxCollider(ColliderManager *colliderManager,
                                     int ID){
    if(colliderManager->numOfBoxColliders - 1 != 0){
        // Allocate memory for smaller array
        BoxCollider **newBoxColliders = calloc(colliderManager->numOfBoxColliders - 1, sizeof(BoxCollider));
        // Only copy elements that are not to be removed
        for(size_t i = 0; i < colliderManager->numOfBoxColliders - 1; ++i){
            if(colliderManager->BoxColliders[i]->ID != ID){
                newBoxColliders[i] = colliderManager->BoxColliders[i];
            }
        }
        // free old array
        free(colliderManager->BoxColliders);
        // assign new array to colliderManager
        colliderManager->BoxColliders = newBoxColliders;
    }
    else{
        // if size = 0, store null pointer
        free(colliderManager->BoxColliders);
        colliderManager->BoxColliders = NULL;
    }
}

void ColliderManager_addSphereCollider(ColliderManager *colliderManager,
                          SphereCollider *sphereCollider){
    // Allocate new, larger array
    if(colliderManager->SphereColliders == NULL){
        colliderManager->SphereColliders = calloc(1, sizeof(SphereCollider));
    }
    else{
        colliderManager->SphereColliders = realloc(colliderManager->SphereColliders, sizeof(SphereCollider) * colliderManager->numOfSphereColliders + 1);
    }
    // Copy SphereCollider object into array
    colliderManager->SphereColliders[colliderManager->numOfSphereColliders] = sphereCollider;
    // Assign ID to BoxCollider
    colliderManager->SphereColliders[colliderManager->numOfSphereColliders]->ID = getID(colliderManager);
    colliderManager->numOfSphereColliders++;
    colliderManager->numOfColliders++;
}

void ColliderManager_rmSphereCollider(ColliderManager *colliderManager,
                                        int ID){
    if(colliderManager->numOfSphereColliders - 1 != 0){
        // Allocate memory for smaller array
        SphereCollider **newSphereColliders = calloc(colliderManager->numOfSphereColliders - 1, sizeof(SphereCollider));
        // Only copy elements that are not to be removed
        for(size_t i = 0; i < colliderManager->numOfSphereColliders - 1; ++i){
            if(colliderManager->SphereColliders[i]->ID != ID){
                newSphereColliders[i] = colliderManager->SphereColliders[i];
            }
        }
        // free old array
        free(colliderManager->SphereColliders);
        // assign new array to colliderManager
        colliderManager->SphereColliders = newSphereColliders;
    }
    else{
        // if size = 0, store null pointer
        free(colliderManager->SphereColliders);
        colliderManager->SphereColliders = NULL;
    }
}

