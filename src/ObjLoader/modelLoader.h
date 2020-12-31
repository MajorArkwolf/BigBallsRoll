#pragma once
#include "ObjLoader/model.h"

/**
 * Load Obj or Off file format into Memory.
 * @param workingDir the directory relative to the executable location minus the exe name.
 * @param fileName file name you wish to load relative to the resource directory.
 * @return the loaded model if successful.
 */
Model ModelLoader_loadModel(char *workingDir, char *fileName);

/**
 * Allocate the required quantities for the Mesh
 * @param mesh the mesh to allocate into
 * @param faces the amount of faces to allocate
 * @param vertices the amount of vertices to allocate
 * @return true if passed or false if failed
 */
bool ModelLoader_allocateMesh(Mesh *mesh, size_t faces, size_t vertices);

/**
 * Load OFF file format
 * @param model Model to populate
 * @param fptr the file pointer to get the data from
 * @return true if succeeded or false if failed.
 */
bool ModelLoader_loadOff(Model *model, FILE *fptr);