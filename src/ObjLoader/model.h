#pragma once
#include <stdio.h>
typedef struct Vertex {
    float X;
    float Y;
    float Z;
} Vertices;

typedef struct Face {
    size_t One;
    size_t Two;
    size_t Three;
} Face;

typedef struct Model {
    Face *Faces;
    Vertices *Vertices;
    size_t NumOfFaces;
    size_t NumOfVert;
} Model;

void model_initModel(Model *model);

void model_free(Model *model);
