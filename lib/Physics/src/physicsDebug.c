#include "include/BigBalls/physicsDebug.h"
#include <assert.h>

void PhysicsDebug_dataInit(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    debug->colour[0] = 255;
    debug->colour[1] = 255;
    debug->colour[2] = 0;
    debug->vertices = calloc(1, sizeof(FloatArray));
    debug->faceIndexes = calloc(1, sizeof(SizeTArray));
    DynamicArray_initFloat(debug->vertices);
    DynamicArray_initSizeT(debug->faceIndexes);
}

void PhysicsDebug_dataReset(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    DynamicArray_eraseFloat(debug->vertices);
    DynamicArray_eraseSizeT(debug->faceIndexes);
}

void PhysicsDebug_dataFree(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    DynamicArray_freeFloat(debug->vertices);
    DynamicArray_freeSizeT(debug->faceIndexes);
    free(debug->vertices);
    free(debug->faceIndexes);
}

void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd, const size_t *faceOrder, size_t faceOrderSize) {
    assert(collisionBody != NULL && dd != NULL && faceOrder != NULL);

    size_t beforeMaxLengthVert = dd->vertices->size;

    //0 (vertex order)
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2);

    //1
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1);

    //2
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1);

    //3
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2);

    //4
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1);

    //5
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1);

    //6
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2);

    //7
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2);

    //TODO: Put here? and dont pass anything in? if only rendering cubes this will be fine. Not scalable otherwise.
    //size_t faceOrder[36] = {2,1,0,0,3,2,5,4,1,1,2,5,7,6,4,4,5,7,3,0,6,6,7,3,4,6,0,0,1,4,5,2,3,3,7,5};

    for (size_t i = 0; i < faceOrderSize; ++i) {
        DynamicArray_pushBackSizeT(dd->faceIndexes, beforeMaxLengthVert + faceOrder[i] * 3);
    }
}
