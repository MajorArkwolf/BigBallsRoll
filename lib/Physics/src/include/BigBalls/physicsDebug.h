#pragma once
#include "collisionBody.h"
#include "dynamicArray.h"

typedef struct DebugData {
    size_t numFaces;
    size_t numVertices;
    FloatArray *vertices;
    SizeTArray *faceIndexes;
    float colour[3];
} DebugData;

/**
 * Initialise the DebugData object, must be called before using.
 * @param debug the object to initialise
 */
void PhysicsDebug_dataInit(DebugData *debug);

void PhysicsDebug_dataReset(DebugData *debug);

void PhysicsDebug_dataFree(DebugData *debug);

void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd, const size_t *faceOrder, size_t faces);

