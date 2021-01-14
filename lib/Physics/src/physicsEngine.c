#include "include/BigBalls/physicsEngine.h"
#include "include/BigBalls/collisionBodyManager.h"
#include <stdbool.h>
#include <stdlib.h>

void collisionBodyManager(){
    // init collider manager
}

void physicsWorldInit(){
    // init collision body manager
}

size_t createCollisionBody(){
    // Allocate memory for collisionbody
    // Add memory to collision body manager and get ID from manager
    return 0; // stub
}

bool destroyCollisionBody(size_t ID){
    return true; // stub
}

void createBoxCollider(size_t ID,
                       size_t xOffset,
                       size_t yOffset,
                       size_t zOffset,
                       size_t xLen,
                       size_t yLen,
                       size_t zLen){

}

void destroyBoxCollider(){

}

void createSphereCollider(size_t ID,
                          size_t xOffset,
                          size_t yOffset,
                          size_t zOffset,
                          size_t radius){

}

void destroySphereCollider(){

}
