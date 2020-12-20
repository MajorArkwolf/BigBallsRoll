#include "objLoader.h"
#include <stdarg.h>
#include <stdlib.h>

Model loadModel(char *fileName, size_t length) {
    Model model;
    model.numOfFaces = 0;
    model.numOfVert = 0;
    model.vertices = NULL;
    model.face = NULL;

    return model;
}
