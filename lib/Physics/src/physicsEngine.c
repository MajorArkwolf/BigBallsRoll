#include "include/BigBalls/physicsEngine.h"

#include <stdlib.h>
#include <assert.h>
#include "include/BigBalls/physicsWorld.h"

//TODO: Arbitrary number, find out if its necessary to be dynamic
#define PHYSICS_WORLD_MAX 15

void PhysicsEngine_init(PhysicsEngine *physicsEngine) {
    //TODO: confirm this will work, dont want people calling this when PW is not null and causing leaks
    assert(physicsEngine != NULL && physicsEngine->physicsWorld == NULL);
    physicsEngine->physicsWorld = calloc(PHYSICS_WORLD_MAX, sizeof(PhysicsWorld));
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
