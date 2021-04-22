#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "Math/vec3.h"
#include "Engine/textureManager.h"

/// Colour represented in RGBA format and in that order.
typedef struct Colour {
    float RGBA[4];
} Colour;

typedef struct TextureCord {
    float T[2];
} TextureCord;

/// Vertex data
typedef struct Vertex {
    float X;
    float Y;
    float Z;
} Vertex;

typedef struct Point {
    int VertexID;
    int TextureID;
    int NormalID;
} Point;

/// Face Data
typedef struct Face {
    Colour Colour;
    size_t NumFaces;
    Point *Point;
    int MaterialIndex;
    bool HasColour;
} Face;

typedef struct Material {
    //Ka
    float Ambient[4];
    //Kd
    float Diffuse[4];
    //Ks
    float Specular[4];
    //Ni (weight for spec)
    float OpticalWeight;
    // kd texture
    Texture *DiffuseTexture;
    //Material Name
    char *MaterialName;
} Material;

/// Mesh Data
typedef struct Mesh {
    Face *Faces;
    Vertex *Vertices;
    Vertex *Normals;
    TextureCord *TextureCords;
    Material *Materials;
    size_t NumOfFaces;
    size_t NumOfVert;
    size_t NumOfNormals;
    size_t NumOfTextureCords;
    size_t NumOfMaterials;
} Mesh;

/// Model Data
typedef struct Model {
    Mesh *Mesh;
    size_t NumOfMesh;
    char *Name;
} Model;

/**
 * Initialise vertex
 * @param vertex must be instantiated before parsing in.
 */
void Vertex_init(Vertex *vertex);

/**
 * Initialise Face
 * @param face must be instantiated before parsing in.
 */
void Face_init(Face *face);

/**
 * Free Face
 * @param face
 */
void Face_free(Face *face);

/**
 * Initialise Model
 * @param model must be instantiated before parsing in.
 */
void Model_init(Model *model);

/**
 * Draw model, should not be called outside of the renderer or game object.
 * @param model
 */
void Model_draw(Model *model);

/**
 * Free Model
 * @param model
 */
void Model_free(Model *model);

/**
 * Initialise Mesh
 * @param mesh
 */
void Mesh_init(Mesh *mesh);

/**
 * Free Mesh
 * @param mesh
 */
void Mesh_free(Mesh *mesh);

/**
 * Sums two colours together
 * @param firstColour first colour to sum.
 * @param secondColour second colour to sum.
 * @return the result of those two colours.
 */
Colour Colour_addColourToColour(Colour *firstColour, Colour *secondColour);

/**
 * Normalise the colour, Alpha channel will be ignored.
 * @param colour this variable will be altered.
 */
void Colour_NormaliseColour(Colour *colour);

/**
 * Initialises point data
 * @param point the point data to be initialised
 */
void Point_init(Point *point);

/**
 * Initialises a material data
 * @param material the material data to tbe initialised
 */
void Material_init(Material *material);

/**
 * Find a material with in a mesh
 * @param mesh the mesh to search
 * @param materialName the material name to look for
 * @return -1 on failure or 0+ on valid index
 */
int Mesh_findMaterial(Mesh *mesh, char* materialName);
