#include "include/BigBalls/physicsDebug.h"
#include <assert.h>
#include <stdio.h>

//AABB face order
const size_t AABBFaceOrder[36] = {2,1,0,0,3,2,5,4,1,1,2,5,7,6,4,4,5,7,3,0,6,6,7,3,4,6,0,0,1,4,5,2,3,3,7,5};
//Face colours
const size_t BroadPhaseDebugColour[3] = {255,255,0}; // Yellow

void PhysicsDebug_dataInit(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
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

void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd) {
    assert(collisionBody != NULL && dd != NULL);

    const size_t beforeMaxLengthVert = dd->vertices->size;

    //0 (vertices)
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

    const size_t numFaceIndices = 36;

    for (size_t i = 0; i < numFaceIndices; ++i) {
        //Push back index
        DynamicArray_pushBackSizeT(dd->faceIndexes, beforeMaxLengthVert + AABBFaceOrder[i] * 3);
        //Push back RGB
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[0]);
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[1]);
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[2]);
    }
}
