#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Vertex {
    float X;
    float Y;
    float Z;
} Vertex;

typedef struct Face {
    size_t NumFaces;
    size_t *FaceIDs;
} Face;

typedef struct Model {
    Face *Faces;
    Vertex *Vertices;
    size_t NumOfFaces;
    size_t NumOfVert;
} Model;

void Face_initFace(Face *face);

void Face_free(Face *face);

void Model_initModel(Model *model);

void Model_free(Model *model);

bool Model_modelToOFF(Model *model);
