#pragma once
#include "collisionBody.h"
#include "dynamicArray.h"

/**
 * DebugData object.
 *
 * FaceIndexes contains the index to the first of its three vertices which are stored in *vertices, as well as the colour of that face.
 * The first 3 values represent the R,G,B values of that face.
 * The 4th value in FaceIndexes will be the index to the first face.
 * Format is as follows: R,G,B,FACE_INDEX,R,G,B,FACE_INDEX...
 */
typedef struct DebugData {
    size_t numFaces;
    size_t numVertices;
    FloatArray *vertices;
    SizeTArray *faceIndexes;
    FloatArray *sphereData;     //r, X, Y, Z
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
 * After adding a face index a RBG value is also stored for that face.
 * @param collisionBody The collision body to generate vertices and face indices for.
 * @param dd The debug object to store this info in.
 */
void PhysicsDebug_generateAABBBox(CollisionBody *collisionBody, DebugData *dd);

/**
 * Stores the sphere collider radius and coordinates (x,y,z) into the debugData's
 * sphereData array. Stores in order radius, x, y, z.
 * @param collisionBody The collision body to retrieve the coordinates and radius from.
 * @param dd The debug object to store this info in.
 */
void PhysicsDebug_generateSphereData(CollisionBody *collisionBody, DebugData *dd);
