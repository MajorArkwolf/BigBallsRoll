#include "include/BigBalls/physicsWorld.h"
#include <assert.h>
#include <stdio.h>

int PhysicsWorld_newCollisionBodyID(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    // increment internal ID count and return new ID
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

bool testAABBCollision(CollisionBody *a, CollisionBody *b){
    assert(a != NULL && b != NULL);
    // the min and max points of each CollisionBody, which will be used to determine if the two AABB's of the CollisionBodies are intersecting (colliding)
    float x1min, x1max, y1min, y1max, z1min, z1max, x2min, x2max, y2min, y2max, z2min, z2max;

    // determine which coordinate is larger than the other, for each coordinate pair of each CollisionBody
    minMax(a->AABBx1, a->AABBx2, &x1min, &x1max);
    minMax(a->AABBy1, a->AABBy2, &y1min, &y1max);
    minMax(a->AABBz1, a->AABBz2, &z1min, &z1max);

    minMax(b->AABBx1, b->AABBx2, &x2min, &x2max);
    minMax(b->AABBy1, b->AABBy2, &y2min, &y2max);
    minMax(b->AABBz1, b->AABBz2, &z2min, &z2max);

    return (x1min <= x2max && x1max >= x2min) &&
           (y1min <= y2max && y1max >= y2min) &&
           (z1min <= z2max && z1max >= z2min);
}

void detectCollisions(PhysicsWorld* physicsWorld){
    assert(physicsWorld != NULL);
    // TODO: ideally shouldn't check every body against each other - spacial partitioning method ideal
    // broad phase
    for(size_t i = 0; i < physicsWorld->numCollisionBodies; ++i){
        for(size_t j = i + 1; j < physicsWorld->numCollisionBodies; ++j){ // only checks collisions of different CollisionBodies, where j is always greater than i
                                                                          // (avoids repeat inverse tests eg. checking 1-0 AND 0-1 would be redundant and inefficient)
            if(testAABBCollision(physicsWorld->collisionBodies[i], physicsWorld->collisionBodies[j])) {
                // broad phase collision detected
                printf("Objects %d and %d are colliding!\n", (int)i ,(int)j);
                // TODO: narrow phase
                // TODO: resolve collision
            }
        }
    }
}

void PhysicsWorld_init(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    physicsWorld->collisionBodies = NULL;
    physicsWorld->numCollisionBodies = 0;
    physicsWorld->collisionBodyIdCount = 0;
    physicsWorld->gravity = 1; //TODO: find default
    //physicsWorld->gravityNormal = GravityNormal_init(); TODO: Implement
    physicsWorld->debug = false;
}

void PhysicsWorld_free(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
        CollisionBody_free(physicsWorld->collisionBodies[i]);
    }
    free(physicsWorld);
    physicsWorld = NULL;
}

void PhysicsWorld_update(PhysicsWorld *physicsWorld, float deltaTime){
    assert(physicsWorld != NULL);
    // TODO: implement deltaTime
    detectCollisions(physicsWorld);
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
        //TODO: Implement and get the stuffs

        //TODO: Is this even a good idea? or just make faceOrder inside genAABBBox? Not sure where we would
        //Even get face order from? I doubt a collision body would store it. and is static bad idea?
        //New order (me)
        static size_t faceOrder[36] = {2,1,0,0,3,2,5,4,1,1,2,5,7,6,4,4,5,7,3,0,6,6,7,3,4,6,0,0,1,4,5,2,3,3,7,5};
        //OG order (me + peter)
        //static size_t faceOrder[36] = {0,1,2,2,3,0,1,4,5,5,2,1,4,6,7,7,5,4,6,0,3,3,7,6,4,1,0,0,6,4,5,2,3,3,7,5};
        for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
            PhysicsDebug_generateAABBBox(physicsWorld->collisionBodies[i], debug, faceOrder, 36);
        }
        debug->numVertices = debug->vertices->size;
        debug->numFaces = debug->faceIndexes->size;
        return true;
    }
    return false;
}

void PhysicsWorld_debugToggle(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    if (physicsWorld->debug) {
        physicsWorld->debug = false;
    } else {
        physicsWorld->debug = true;
    }
}

//TODO: Implement
void PhysicsWorld_updateGravityNormal(float x, float y, float z) {
    //TODO: Stub
}

//TODO: Temporary
/*GravityNormal GravityNormal_init() {
    GravityNormal gN;
    gN.X = 0.0f;
    gN.Y = 1.0f;
    gN.Z = 0.0f;
    return gN;
}*/
