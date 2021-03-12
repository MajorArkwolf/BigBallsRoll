#pragma once
#include "collisionBody.h"
#include "dynamicArray.h"

/**
 * DebugData object.
 *
 * FaceIndexes contains the index to the first of its three vertices which are stored in *vertices, as well as the colour of that face.
 * The first value in FaceIndexes will be the index to the first face.
 * The 3 values following this represent the R,G,B values of that face.
 * Format is as follows: FACE_INDEX,R,G,B,FACE_INDEX,R,G,B....
 */
typedef struct DebugData {
    size_t numFaces;
    size_t numVertices;
    FloatArray *vertices;
    SizeTArray *faceIndexes;
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
void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd);

