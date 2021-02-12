#include "include/BigBalls/physicsWorld.h"
#include <assert.h>

int PhysicsWorld_newCollisionBodyID(PhysicsWorld *physicsWorld) {
    assert(physicsWorld != NULL);
    // increment internal ID count and return new ID
    return ++physicsWorld->collisionBodyIdCount;
}

CollisionBody* PhysicsWorld_findCollisionBody(PhysicsWorld *physicsWorld, const int ID) {
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

}

bool PhysicsWorld_moveObj(PhysicsWorld *physicsWorld,
                          int id,
                          float newXOffset,
                          float newYOffset,
                          float newZOffset){
    // check that the object does not collide with other objects at new position
}

GravityNormal* PhysicsWorld_getObjPos(PhysicsWorld *physicsWorld, const int id){
    CollisionBody* target = PhysicsWorld_findCollisionBody(physicsWorld, id);
    if (target == NULL) { // object not found
        return NULL;
    }
    GravityNormal *res = calloc(1, sizeof(GravityNormal));
    res->X = target->xPos;
    res->Y = target->yPos;
    res->Z = target->zPos;
    return res;
}

GravityNormal* PhysicsWorld_getObjRot(PhysicsWorld *physicsWorld, const int id){
    CollisionBody* target = PhysicsWorld_findCollisionBody(physicsWorld, id);
    if (target == NULL) { // object not found
        return NULL;
    }
    GravityNormal *res = calloc(1, sizeof(GravityNormal));
    res->X = target->xRot;
    res->Y = target->yRot;
    res->Z = target->zRot;
    return res;
}

void PhysicsWorld_createObjAABB(PhysicsWorld *physicsWorld,
                                const int ID,
                                const float* vertsX,
                                const float* vertsY,
                                const float* vertsZ,
                                const int numVerts){
    assert(numVerts > 0 && physicsWorld != NULL);
    CollisionBody* target = PhysicsWorld_findCollisionBody(physicsWorld, ID);
    assert(target != NULL); // ensure that object exists before processing
    // init values
    float greatestX = vertsX[0];
    float lowestX = vertsX[0];
    float greatestY = vertsY[0];
    float lowestY = vertsY[0];
    float greatestZ = vertsZ[0];
    float lowestZ = vertsZ[0];
    for(int i = 1; i < numVerts; ++i){
        if(vertsX[i] > greatestX){ // x
            greatestX = vertsX[i];
        }
        if(vertsX[i] < lowestX){
            lowestX = vertsX[i];
        }
        if(vertsY[i] > greatestY){ // y
            greatestY = vertsY[i];
        }
        if(vertsY[i] < lowestY){
            lowestY = vertsY[i];
        }
        if(vertsZ[i] > greatestZ){ // z
            greatestZ = vertsZ[i];
        }
        if(vertsZ[i] < lowestZ){
            lowestZ = vertsZ[i];
        }
    }
    // got dimensions for box, assign to CollisionBody
    target->AABBx1 = lowestX;
    target->AABBx2 = greatestX;
    target->AABBy1 = lowestY;
    target->AABBy2 = greatestY;
    target->AABBz1 = lowestZ;
    target->AABBz2 = greatestZ;
}

bool testAABBCollision(const float X1POS,
                       const float Y1POS,
                       const float Z1POS,
                       const float X1LEN,
                       const float Y1LEN,
                       const float Z1LEN,
                       const float X2POS,
                       const float Y2POS,
                       const float Z2POS,
                       const float X2LEN,
                       const float Y2LEN,
                       const float Z2LEN){
    const float D1X = X1POS - (X2POS + X2LEN);
    const float D1Y = Y1POS - (Y2POS + Y2LEN);
    const float D1Z = Z1POS - (Z2POS + Z2LEN);
    const float D2X = X2POS - (X1POS + X1LEN);
    const float D2Y = Y2POS - (Y1POS + Y1LEN);
    const float D2Z = Z2POS - (Z1POS + Z1LEN);

    // if smallest coord of a box is greater than largest x coord of other box, the boxes cannot be colliding
    return D1X > 0.0f || D1Y > 0.0f || D1Z > 0.0f || D2X > 0.0f || D2Y > 0.0f || D2Z > 0.0f ? false : true;
}

void detectCollisions(PhysicsWorld* physicsWorld){
    // TODO: ideally shouldn't check every body against each other - spacial partitioning method ideal
    // broad phase
    for(size_t i = 0; physicsWorld->numCollisionBodies; ++i){
        for(size_t j = 0; physicsWorld->numCollisionBodies; j++){
            if(i != j){ // dont check for collision of the same object
                if(testAABBCollision(physicsWorld->collisionBodies[i]->AABBx1, // obj 1
                                  physicsWorld->collisionBodies[i]->AABBy1,
                                  physicsWorld->collisionBodies[i]->AABBz1,
                                  physicsWorld->collisionBodies[i]->AABBx2-physicsWorld->collisionBodies[i]->AABBx1,
                                  physicsWorld->collisionBodies[i]->AABBy2-physicsWorld->collisionBodies[i]->AABBy1,
                                  physicsWorld->collisionBodies[i]->AABBz2-physicsWorld->collisionBodies[i]->AABBz1,
                                  physicsWorld->collisionBodies[j]->AABBx1, // obj 2
                                  physicsWorld->collisionBodies[j]->AABBy1,
                                  physicsWorld->collisionBodies[j]->AABBz1,
                                  physicsWorld->collisionBodies[j]->AABBx2-physicsWorld->collisionBodies[i]->AABBx1,
                                  physicsWorld->collisionBodies[j]->AABBy2-physicsWorld->collisionBodies[i]->AABBy1,
                                  physicsWorld->collisionBodies[j]->AABBz2-physicsWorld->collisionBodies[i]->AABBz1)) {
                    // broad phase collision detected
                    // TODO: narrow phase
                    // TODO: resolve collision
                }
            }
        }
    }
}

void PhysicsWorld_addCollisionBody(PhysicsWorld *physicsWorld, CollisionBody *collisionBody) {
    assert(physicsWorld != NULL);
    // Allocate new, larger array
    if (physicsWorld->collisionBodies == NULL) {
        physicsWorld->collisionBodies = calloc(1, sizeof(CollisionBody));
    } else {
        physicsWorld->collisionBodies = realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * physicsWorld->numCollisionBodies + 1);
    }
    // Copy BoxCollider object into array
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies] = collisionBody;
    // Assign ID to BoxCollider
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies]->id = PhysicsWorld_newCollisionBodyID(physicsWorld);
    physicsWorld->numCollisionBodies++;
}

void PhysicsWorld_removeCollisionBody(PhysicsWorld *physicsWorld, const int ID) {
    assert(physicsWorld != NULL);
    for (size_t i = 0; i < physicsWorld->numCollisionBodies; ++i) {
        if (physicsWorld->collisionBodies[i]->id == ID) {
            CollisionBody_free(physicsWorld->collisionBodies[i]);
            for (size_t j = i + 1; j < physicsWorld->numCollisionBodies; ++j) { // for each collisionbody after match index
                physicsWorld->collisionBodies[j - 1] = physicsWorld->collisionBodies[j];
            }
            physicsWorld->collisionBodies[physicsWorld->numCollisionBodies - 1] = NULL;
            --physicsWorld->numCollisionBodies;
            // reduce size of memory allocation (shouldn't be costly if realloc() realises whats going on)
            realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * physicsWorld->numCollisionBodies);
        }
    }
}

//TODO: Implement
void PhysicsWorld_updateGravityNormal(float x, float y, float z) {
    //Stub
}

//TODO: Temporary
GravityNormal GravityNormal_init() {
    GravityNormal gN;
    gN.X = 0.0f;
    gN.Y = 1.0f;
    gN.Z = 0.0f;
    return gN;
}
