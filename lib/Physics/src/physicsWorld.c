#include "include/BigBalls/physicsWorld.h"
#include <assert.h>

CollisionBody *PhysicsWorld_registerCollisionBody(PhysicsWorld *physicsWorld) {
    CollisionBody *cp = calloc(1, sizeof(CollisionBody));
    PhysicsWorld_addCollisionBody(physicsWorld, cp);
    return cp;
}

int PhysicsWorld_newCollisionBodyID(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    return ++physicsWorld->collisionBodyIdCount;
}

CollisionBody* PhysicsWorld_findCollisionBody(PhysicsWorld *physicsWorld, const int ID) {
    assert(physicsWorld != NULL && ID >= 0);
    for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
        if (physicsWorld->collisionBodies[i]->id == ID) {
            return physicsWorld->collisionBodies[i];
        }
    }
    return NULL;
}

void PhysicsWorld_init(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    physicsWorld->collisionBodies = NULL;
    physicsWorld->numCollisionBodies = 0;
    physicsWorld->collisionBodyIdCount = 0;
    physicsWorld->gravity = PVec3_init();
    physicsWorld->gravity.data[2] = -9.8f;
    physicsWorld->debug = false;
}

void PhysicsWorld_free(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
        CollisionBody_free(physicsWorld->collisionBodies[i]);
    }
    free(physicsWorld);
}

void PhysicsWorld_addCollisionBody(PhysicsWorld *physicsWorld, CollisionBody *collisionBody) {
    assert(physicsWorld != NULL && collisionBody != NULL);
    // Allocate new, larger array
    if (physicsWorld->collisionBodies == NULL) {
        physicsWorld->collisionBodies = calloc(1, sizeof(CollisionBody));
    } else {
        physicsWorld->collisionBodies = realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * (physicsWorld->numCollisionBodies + 1));
    }
    // Copy BoxCollider object into array
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies] = collisionBody;
    // Assign ID to BoxCollider
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies]->id = PhysicsWorld_newCollisionBodyID(physicsWorld);
    ++physicsWorld->numCollisionBodies;
}

void PhysicsWorld_removeCollisionBody(PhysicsWorld *physicsWorld, const int ID) {
    assert(physicsWorld != NULL && ID >= 0);
    for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
        if (physicsWorld->collisionBodies[i]->id == ID) {
            CollisionBody_free(physicsWorld->collisionBodies[i]);
            for (size_t j = i + 1; j < physicsWorld->numCollisionBodies; ++j) { // for each collisionbody after match index
                physicsWorld->collisionBodies[j - 1] = physicsWorld->collisionBodies[j];
            }
            physicsWorld->collisionBodies[physicsWorld->numCollisionBodies - 1] = NULL;
            --physicsWorld->numCollisionBodies;
            // reduce size of memory allocation (shouldn't be costly if realloc() realises whats going on)
            physicsWorld->collisionBodies = realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * physicsWorld->numCollisionBodies);
        }
    }
}

bool PhysicsWorld_draw(PhysicsWorld *physicsWorld, DebugData *debug) {
    assert(physicsWorld != NULL && debug != NULL);
    if (physicsWorld->debug) {
        //Reset the object
        PhysicsDebug_dataReset(debug);

        for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
            PhysicsDebug_generateAABBBox(physicsWorld->collisionBodies[i], debug);
        }
        debug->numVertices = debug->vertices->size;
        debug->numFaces = debug->faceIndexes->size;
        return true;
    }
    return false;
}

void PhysicsWorld_debugToggle(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    physicsWorld->debug = !physicsWorld->debug;
}

void PhysicsWorld_updateGravityNormal(PhysicsWorld *physicsWorld, float x, float y, float z) {
    physicsWorld->gravity.data[0] = x;
    physicsWorld->gravity.data[1] = y;
    physicsWorld->gravity.data[2] = z;
}
