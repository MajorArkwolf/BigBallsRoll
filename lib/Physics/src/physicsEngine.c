#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "include/BigBalls/physicsEngine.h"

void PhysicsEngine_init(PhysicsEngine *physicsEngine) {
    assert(physicsEngine != NULL && physicsEngine->physicsWorld == NULL); // would cause leaks if PhysicsWorld is not NULL
    physicsEngine->physicsWorld = calloc(1, sizeof(PhysicsWorld**));
    physicsEngine->numOfPhysicsWorlds = 0;
}

void PhysicsEngine_free(PhysicsEngine *physicsEngine) {
    assert(physicsEngine != NULL);
    for (size_t i = 0; i < physicsEngine->numOfPhysicsWorlds; ++i) {
        if (physicsEngine->physicsWorld != NULL) {
            PhysicsWorld_free(physicsEngine->physicsWorld[i]);
        }
    }
    free(physicsEngine->physicsWorld);
    physicsEngine->numOfPhysicsWorlds = 0;
}

PhysicsWorld* PhysicsEngine_newPhysicsWorld(PhysicsEngine *physicsEngine) {
    assert(physicsEngine != NULL);
    if(physicsEngine->numOfPhysicsWorlds == 0){
        physicsEngine->physicsWorld[0] = calloc(1, sizeof(PhysicsWorld));
    }
    else{
        physicsEngine->physicsWorld = realloc(physicsEngine->physicsWorld, sizeof(PhysicsWorld) * physicsEngine->numOfPhysicsWorlds);
    }
    //initialise new Physics World
    PhysicsWorld_init(physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds]);
    assert(physicsEngine->physicsWorld != NULL);
    ++physicsEngine->numOfPhysicsWorlds;
    return physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds - 1];
}

void PhysicsEngine_freePhysicsWorld(PhysicsEngine *physicsEngine, PhysicsWorld *physicsWorld) {
    assert(physicsEngine != NULL);
    for (size_t i = 0; i < physicsEngine->numOfPhysicsWorlds; ++i) {
        //Find index of physicsWorld so we can consolidate array
        if (physicsEngine->physicsWorld[i] == physicsWorld) {
            PhysicsWorld_free(physicsEngine->physicsWorld[i]);
            //Consolidate array
            for (size_t j = i; j < physicsEngine->numOfPhysicsWorlds; ++j) {
                physicsEngine->physicsWorld[j - 1] = physicsEngine->physicsWorld[j];
            }
            physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds] = NULL;
            --physicsEngine->numOfPhysicsWorlds;
            break;
        }
    }
}
