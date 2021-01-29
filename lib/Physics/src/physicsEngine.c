#include "include/BigBalls/physicsEngine.h"

#include <stdlib.h>
#include <assert.h>
#include "include/BigBalls/physicsWorld.h"

void PhysicsEngine_init(PhysicsEngine *physicsEngine) {
    physicsEngine->physicsWorld = NULL;
}

void PhysicsEngine_newPhysicsWorld(PhysicsEngine *physicsEngine){
    assert(physicsEngine != NULL);
    // Create new Physics World
    if (physicsEngine->physicsWorld == NULL) {
        PhysicsWorld_init(physicsEngine->physicsWorld);
    } else {
        PhysicsWorld_free(physicsEngine->physicsWorld);
        PhysicsWorld_init(physicsEngine->physicsWorld);
    }
    assert(physicsEngine->physicsWorld != NULL);
}

int PhysicsEngine_createCollisionBody(PhysicsEngine *physicsEngine){
    assert(physicsEngine != NULL);
    // Allocate memory for collisionbody
    // Add memory to collision body manager and get ID from manager
    return 0; // stub
}

bool PhysicsEngine_destroyCollisionBody(PhysicsEngine *physicsEngine,
                          int id){
    assert(physicsEngine != NULL);
    return true; // stub
}
