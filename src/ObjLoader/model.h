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
    Colour Colour;
    size_t NumFaces;
    size_t *FaceIDs;
    bool HasColour;
} Face;

typedef struct Mesh {
    Face *Faces;
    Vertex *Vertices;
    size_t NumOfFaces;
    size_t NumOfVert;
} Mesh;

typedef struct Model {
    Mesh *Mesh;
    size_t NumOfMesh;
    char *Name;
} Model;

void Vertex_init(Vertex *vertex);

void Face_initFace(Face *face);

void Face_free(Face *face);

void Model_initModel(Model *model);

void Model_draw(Model *model);

void Model_free(Model *model);

void Mesh_initMesh(Mesh *mesh);

bool Model_modelToOFF(Model *model);

void Mesh_free(Mesh *mesh);

Colour Colour_addColourToColour(Colour *firstColour, Colour *secondColour);

void Colour_NormaliseColour(Colour *colour);
