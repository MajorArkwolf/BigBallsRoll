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
    assert(physicsEngine->physicsWorld != NULL);
    // Allocate memory for collisionbody
    // Add memory to collision body manager and get ID from manager
    CollisionBody *newCB = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(newCB);
    PhysicsWorld_addCollisionBody(physicsEngine->physicsWorld, newCB);

    return newCB->id;
}

bool PhysicsEngine_destroyCollisionBody(PhysicsEngine *physicsEngine,
                          int id){
    assert(physicsEngine != NULL);
    PhysicsWorld_removeCollisionBody(physicsEngine->physicsWorld, id);
    return true; // stub
}
