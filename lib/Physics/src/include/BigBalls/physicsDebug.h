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

/**
 * Resets the dynamic arrays and counts.
 * @param debug the object to reset.
 */
void PhysicsDebug_dataReset(DebugData *debug);

/**
 * Frees a DebugData object.
 * @param debug the object to free.
 */
void PhysicsDebug_dataFree(DebugData *debug);

/**
 * Generates the vertices and Face indexes for a CollisionBody. Updates the DebugData object with this new information.
 * @param collisionBody The collision body to generate vertices and face indices for.
 * @param dd The debug object to store this info in.
 * @param faceOrder The Face vertices order.
 * @param faceOrderSize The size of the faceOrder Array.
 */
void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd, const size_t *faceOrder, size_t faceOrderSize);

