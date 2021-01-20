#include "include/BigBalls/physicsEngine.h"

#include <stdlib.h>
#include <assert.h>
#include "include/BigBalls/collisionBodyManager.h"

void physicsWorldInit(PhysicsEngine *physicsEngine){
    assert(physicsEngine != NULL);
    // init collision body manager
    physicsEngine->collisionBodyManager = NULL;
}

int createCollisionBody(PhysicsEngine *physicsEngine){
    assert(physicsEngine != NULL);
    // Allocate memory for collisionbody
    // Add memory to collision body manager and get ID from manager
    return 0; // stub
}

bool destroyCollisionBody(PhysicsEngine *physicsEngine,
                          int id){
    assert(physicsEngine != NULL);
    return true; // stub
}

void addBroadPhase(){}

void addNarrowPhase(){}
