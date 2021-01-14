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

int createCollisionBody(){
    // Allocate memory for collisionbody
    // Add memory to collision body manager and get ID from manager
    return 0; // stub
}

bool destroyCollisionBody(int ID){
    return true; // stub
}

void createBoxCollider(int ID,
                       float xOffset,
                       float yOffset,
                       float zOffset,
                       float xLen,
                       float yLen,
                       float zLen){
    // check lengths aren't negative
}

void destroyBoxCollider(){

}

void createSphereCollider(int ID,
                          float xOffset,
                          float yOffset,
                          float zOffset,
                          float radius){
    // check radius isn't negative
}

void destroySphereCollider(){

}
