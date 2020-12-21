#pragma once
#include <stdio.h>
typedef struct Vertices {
    float x;
    float y;
    float z;
} Vertices;

typedef struct Face {
    size_t one;
    size_t two;
    size_t three;
} Face;

typedef struct Model {
    Face *face;
    Vertices *vertices;
    int numOfFaces;
    int numOfVert;
} Model;

void initModel(Model *model);