#pragma once

#include <stdio.h>
#include "model.h"

/**
 * Load Obj or Off file format into Memory.
 * @param workingDir the directory relative to the executable location minus the exe name.
 * @param fileName file name you wish to load relative to the resource directory.
 * @return the loaded model if successful.
 */
Model ObjLoader_loadModel(char *workingDir, char *fileName);
