#pragma once

#include <stdio.h>
#include "model.h"

/**
 * Load Obj file format
 * @param model Model to populate
 * @param fptr the file pointer to get the data from
 * @return true if succeeded or false if failed.
 */
bool ObjLoader_loadObj(Model *model, FILE *fptr);

bool ObjLoader_loadMesh(Mesh *mesh, FILE *fptr);