#include "include/BigBalls/physicsDebug.h"
#include <assert.h>

//AABB face order
const size_t AABBFaceOrder[36] = {2,1,0,0,3,2,5,4,1,1,2,5,7,6,4,4,5,7,3,0,6,6,7,3,4,6,0,0,1,4,5,2,3,3,7,5};
//Face colours
const size_t BroadPhaseDebugColour[3] = {234,234,47}; // GOLDEN FIZZ

void PhysicsDebug_dataInit(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    debug->vertices = calloc(1, sizeof(FloatArray));
    debug->faceIndexes = calloc(1, sizeof(SizeTArray));
    debug->sphereData = calloc(1, sizeof(FloatArray));
    DynamicArray_initFloat(debug->vertices);
    DynamicArray_initSizeT(debug->faceIndexes);
    DynamicArray_initFloat(debug->sphereData);
}

void PhysicsDebug_dataReset(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    DynamicArray_eraseFloat(debug->vertices);
    DynamicArray_eraseSizeT(debug->faceIndexes);
    DynamicArray_eraseFloat(debug->sphereData);
}

void PhysicsDebug_dataFree(DebugData *debug) {
    assert(debug != NULL);
    debug->numVertices = 0;
    debug->numFaces = 0;
    DynamicArray_freeFloat(debug->vertices);
    DynamicArray_freeSizeT(debug->faceIndexes);
    DynamicArray_freeFloat(debug->sphereData);
    free(debug->vertices);
    free(debug->faceIndexes);
    free(debug->sphereData);
}

void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd) {
    assert(collisionBody != NULL && dd != NULL);

    const size_t beforeMaxLengthVert = dd->vertices->size;

    //0 (vertices)
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2 + 0.001f);

    //1
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1 - 0.001f);

    //2
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1 - 0.001f);

    //3
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2 + 0.001f);

    //4
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1 - 0.001f);

    //5
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz1 - 0.001f);

    //6
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy2 + 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2 + 0.001f);

    //7
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBx1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBy1 - 0.001f);
    DynamicArray_pushBackFloat(dd->vertices, collisionBody->AABBz2 + 0.001f);

    const size_t numFaces = 12;

    for (size_t i = 0; i < numFaces; ++i) {
        //Push back RGB
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[0]);
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[1]);
        DynamicArray_pushBackSizeT(dd->faceIndexes, BroadPhaseDebugColour[2]);
        for (size_t j = i * 3; j < i * 3 + 3; ++j) {
            //Push back 3 index to make one face
            DynamicArray_pushBackSizeT(dd->faceIndexes, beforeMaxLengthVert + AABBFaceOrder[j] * 3);
        }
    }
}

void PhysicsDebug_generateSphereData(CollisionBody *collisionBody, DebugData *dd) {
    assert(collisionBody != NULL && dd != NULL);

    for (size_t i = 0; i < collisionBody->numOfSphereColliders; ++i) {
        DynamicArray_pushBackFloat(dd->sphereData, collisionBody->SphereColliders[i]->radius);
        DynamicArray_pushBackFloat(dd->sphereData, collisionBody->SphereColliders[i]->xOffset+ collisionBody->xPos);
        DynamicArray_pushBackFloat(dd->sphereData, collisionBody->SphereColliders[i]->yOffset + collisionBody->yPos);
        DynamicArray_pushBackFloat(dd->sphereData, collisionBody->SphereColliders[i]->zOffset + collisionBody->zPos);
    }
}
