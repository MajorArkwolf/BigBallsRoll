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
    // determine which coordinate is larger than the other
    float x1min, x1max, y1min, y1max, z1min, z1max, x2min, x2max, y2min, y2max, z2min, z2max;
    if(a->AABBx1 <= a->AABBx2){ // a
        x1min = a->AABBx1;
        x1max = a->AABBx2;
    }
    else{
        x1min = a->AABBx2;
        x1max = a->AABBx1;
    }
    if(a->AABBy1 <= a->AABBy2){
        y1min = a->AABBy1;
        y1max = a->AABBy2;
    }
    else{
        y1min = a->AABBy2;
        y1max = a->AABBy1;
    }
    if(a->AABBz1 <= a->AABBz2){
        z1min = a->AABBz1;
        z1max = a->AABBz2;
    }
    else{
        z1min = a->AABBz2;
        z1max = a->AABBz1;
    }

    if(b->AABBx1 <= b->AABBx2){ // b
        x2min = b->AABBx1;
        x2max = b->AABBx2;
    }
    else{
        x2min = b->AABBx2;
        x2max = b->AABBx1;
    }
    if(b->AABBy1 <= b->AABBy2){
        y2min = b->AABBy1;
        y2max = b->AABBy2;
    }
    else{
        y2min = b->AABBy2;
        y2max = b->AABBy1;
    }
    if(b->AABBz1 <= b->AABBz2){
        z2min = b->AABBz1;
        z2max = b->AABBz2;
    }
    else{
        z2min = b->AABBz2;
        z2max = b->AABBz1;
    }

    return (x1min <= x2max && x1max >= x2min) &&
           (y1min <= y2max && y1max >= y2min) &&
           (z1min <= z2max && z1max >= z2min);
}

void detectCollisions(PhysicsWorld* physicsWorld){
    assert(physicsWorld != NULL);
    // TODO: ideally shouldn't check every body against each other - spacial partitioning method ideal
    // broad phase
    for(size_t i = 0; i < physicsWorld->numCollisionBodies; ++i){
        for(size_t j = 1; j < physicsWorld->numCollisionBodies; ++j){
            if(i != j && i < j){ // dont check for collision of the same object, or the same pair again (eg. 0 vs 1 AND 1 vs 0)
                if(testAABBCollision(physicsWorld->collisionBodies[i], physicsWorld->collisionBodies[j])) {
                    // broad phase collision detected
                    printf("Objects %d and %d are colliding!\n", (int)i ,(int)j);
                    // TODO: narrow phase
                    // TODO: resolve collision
                }
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
    physicsWorld->gravityNormal = GravityNormal_init();
}

void PhysicsWorld_free(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    for (size_t i = 1; i < physicsWorld->numCollisionBodies; ++i) {
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

//TODO: Implement
void PhysicsWorld_updateGravityNormal(float x, float y, float z) {
    //TODO: Stub
}

//TODO: Temporary
GravityNormal GravityNormal_init() {
    GravityNormal gN;
    gN.X = 0.0f;
    gN.Y = 1.0f;
    gN.Z = 0.0f;
    return gN;
}
