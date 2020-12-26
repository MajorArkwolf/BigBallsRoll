#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <Math/vec3.h>

typedef struct Colour {
    float RGBA[4];
} Colour;

typedef struct Vertex {
    float X;
    float Y;
    float Z;
    bool HasTexture;
    Vec3 Normals;
} Vertex;

typedef struct Face {
    size_t NumFaces;
    size_t *FaceIDs;
    bool HasColour;
    Colour Colour;
} Face;

typedef struct Model {
    Face *Faces;
    Vertex *Vertices;
    size_t NumOfFaces;
    size_t NumOfVert;
} Model;

void Vertex_init(Vertex *vertex);

void Face_initFace(Face *face);

void Face_free(Face *face);

void Model_initModel(Model *model);

void Model_free(Model *model);

bool Model_modelToOFF(Model *model);

Colour Colour_addColourToColour(Colour *firstColour, Colour *secondColour);

void Colour_NormaliseColour(Colour *colour);
