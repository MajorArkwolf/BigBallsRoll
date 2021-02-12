#include "include/BigBalls/collisionBody.h"
#include <assert.h>

void CollisionBody_init(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    collisionBody->numOfColliders = 0;
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->BoxColliders = NULL;
    collisionBody->SphereColliders = NULL;
    collisionBody->idCount = 0;
    collisionBody->id = -1;
    collisionBody->xPos = 0;
    collisionBody->yPos = 0;
    collisionBody->zPos = 0;
    collisionBody->xRot = 0;
    collisionBody->yRot = 0;
    collisionBody->zRot = 0;
    collisionBody->xVel = 0;
    collisionBody->yVel = 0;
    collisionBody->zVel = 0;
    collisionBody->mass = 0;
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
    ++collisionBody->numOfBoxColliders;
    ++collisionBody->numOfColliders;
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
    ++collisionBody->numOfSphereColliders;
    ++collisionBody->numOfColliders;
}

void CollisionBody_translate(CollisionBody *collisionBody,
                             float xDist,
                             float yDist,
                             float zDist){
    collisionBody->xPos += xDist; // update CollisionBody position
    collisionBody->yPos += yDist;
    collisionBody->zPos += zDist;
    // update relative positions of BoxColliders
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->BoxColliders[i]->xOffset += xDist;
        collisionBody->BoxColliders[i]->yOffset += yDist;
        collisionBody->BoxColliders[i]->zOffset += zDist;
    }
    // update relative positions of SphereColliders
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        collisionBody->SphereColliders[i]->xOffset += xDist;
        collisionBody->SphereColliders[i]->yOffset += yDist;
        collisionBody->SphereColliders[i]->zOffset += zDist;
    }
}

void CollisionBody_rotate(CollisionBody *collisionBody,
                          float xRot,
                          float yRot,
                          float zRot){
    collisionBody->xRot += xRot; // update CollisionBody rotation
    collisionBody->yRot += yRot;
    collisionBody->zRot += zRot;
    // update relative rotation of BoxColliders
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->BoxColliders[i]->xRot += xRot;
        collisionBody->BoxColliders[i]->yRot += yRot;
        collisionBody->BoxColliders[i]->zRot += zRot;
    }
    // update relative rotation of SphereColliders
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        collisionBody->SphereColliders[i]->xRot += xRot;
        collisionBody->SphereColliders[i]->yRot += yRot;
        collisionBody->SphereColliders[i]->zRot += zRot;
    }
}

void CollisionBody_scale(CollisionBody *collisionBody,
                         float scaleFactor){
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->BoxColliders[i]->xLen *= scaleFactor;
        collisionBody->BoxColliders[i]->yLen *= scaleFactor;
        collisionBody->BoxColliders[i]->zLen *= scaleFactor;
    }
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->SphereColliders[i]->radius *= scaleFactor;// scale by the average of the three dimensions
    }
}

void CollisionBody_sleep(CollisionBody *collisonBody){
    //TODO: implement
}

void CollisionBody_awake(CollisionBody *collisionBody){
    // TODO: implement
}

void CollisionBody_stop(CollisionBody *collisionBody){
    // TODO: check if stop should do more
    collisionBody->xVel = 0;
    collisionBody->yVel = 0;
    collisionBody->zVel = 0;
    CollisionBody_sleep(collisionBody); // put the collisionbody to sleep so that it isnt considered by collision detection or moved by gravity
}

void CollisionBody_start(CollisionBody *collisionBody){
    CollisionBody_awake(collisionBody);
}

