#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "include/BigBalls/physicsEngine.h"
#include "include/BigBalls/physicsMathsCommon.h"
#include "include/BigBalls/collisionDetection.h"
#include "include/BigBalls/collisionResolution.h"

void PhysicsEngine_init(PhysicsEngine *physicsEngine) {
    assert(physicsEngine != NULL && physicsEngine->physicsWorld == NULL); // would cause leaks if PhysicsWorld is not NULL
    physicsEngine->physicsWorld = NULL;
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
        physicsEngine->physicsWorld = calloc(1, sizeof(PhysicsWorld*));
    }
    else{
        PhysicsWorld *temp = realloc(physicsEngine->physicsWorld, sizeof(PhysicsWorld*) * (physicsEngine->numOfPhysicsWorlds + 1));
        if (temp != NULL) {
            physicsEngine->physicsWorld = temp;
        } else {
            assert(false);
        }
    }
    if (physicsEngine->physicsWorld != NULL) {

        //initialise new Physics World
        PhysicsWorld *pw = calloc(1, sizeof(PhysicsWorld));
        PhysicsWorld_init(pw);
        physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds] = pw;

        ++physicsEngine->numOfPhysicsWorlds;
        return physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds - 1];
    } else {
        assert(false);
        return NULL;
    }
    
}

void PhysicsEngine_freePhysicsWorld(PhysicsEngine *physicsEngine, PhysicsWorld *physicsWorld) {
    assert(physicsEngine != NULL);
    for (size_t i = 0; i < physicsEngine->numOfPhysicsWorlds; ++i) {
        //Find index of physicsWorld so we can consolidate array
        if (physicsEngine->physicsWorld[i] == physicsWorld) {
            PhysicsWorld_free(physicsEngine->physicsWorld[i]);
            //Consolidate array
            for (size_t j = i + 1; j < physicsEngine->numOfPhysicsWorlds; ++j) {
                physicsEngine->physicsWorld[j - 1] = physicsEngine->physicsWorld[j];
            }
            physicsEngine->physicsWorld[physicsEngine->numOfPhysicsWorlds-1] = NULL;
            --physicsEngine->numOfPhysicsWorlds;
            break;
        }
    }
}

void PhysicsEngine_updateWorld(PhysicsWorld *physicsWorld, double deltaTime) {
    if (physicsWorld != NULL) {
        CollisionArrayContainer cac = collisionArrayContainer_init();
        PhysicsWorld_update(physicsWorld, (float)deltaTime);
        collisionsDetection(physicsWorld, &cac);
        collisionResolution(cac.collisionArray, cac.numOfCollisions);
        collisionArrayContainer_free(&cac);
    }
}
