#pragma once

#include <stdio.h>
#include "model.h"

/**
 * Load Obj file format
 * @param model Model to populate
 * @param fptr the file pointer to get the data from
 * @param cwd The directory to the OBJ, important for loading MTL files.
 * @return true if succeeded or false if failed.
 */
bool ObjLoader_loadObj(Model *model, FILE *fptr, char* cwd);

/**
 * Loads a mesh from a model, this should not be called outside the OBJ loader
 * @param mesh a mesh object to be populated
 * @param fptr the file pointer to the mesh
 * @param cwd current working directory, required for any .mtl files
 * @return true if succeeded or false if failed
 */
bool ObjLoader_loadMesh(Mesh *mesh, FILE *fptr, char* cwd);
