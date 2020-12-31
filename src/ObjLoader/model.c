#include "model.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Engine/OpenGL.h"

void Mesh_init(Mesh *mesh) {
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
    mesh->Vertices = NULL;
    mesh->Faces = NULL;
}

void Model_draw(Model *model) {
    for (size_t index = 0; index < model->NumOfMesh; ++index) {
        for (size_t i = 0; i < model->Mesh[index].NumOfFaces; ++i) {
            glBegin(GL_POLYGON);
            for (size_t x = 0; x < model->Mesh[index].Faces[i].NumFaces; ++x) {
                int index_val = model->Mesh[index].Faces[i].Point[x].VertexID;
//                if (model->Mesh[index].Vertices[index_val].HasTexture) {
//                    //TODO: implement textures here
//                }
                if (model->Mesh[index].Faces[i].HasColour) {
                    glColor4f(model->Mesh[index].Faces[i].Colour.RGBA[0], model->Mesh[index].Faces[i].Colour.RGBA[1],
                              model->Mesh[index].Faces[i].Colour.RGBA[2], model->Mesh[index].Faces[i].Colour.RGBA[3]);
                }
                glVertex3f(model->Mesh[index].Vertices[index_val].X, model->Mesh[index].Vertices[index_val].Y,
                           model->Mesh[index].Vertices[index_val].Z);

            }
            glEnd();
        }
    }
}

void Mesh_free(Mesh *mesh) {
    for (size_t i = 0; i < mesh->NumOfFaces; ++i) {
        Face_free(&mesh->Faces[i]);
    }
    free(mesh->Faces);
    free(mesh->Vertices);
    free(mesh->Normals);
    free(mesh->TextureCords);
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
}

void Model_init(Model *model) {
    model->Name = NULL;
    model->NumOfMesh = 0;
    model->Mesh = NULL;
}

void Model_free(Model *model) {
    for (size_t i = 0; i < model->NumOfMesh; ++i) {
        Mesh_free(&model->Mesh[i]);
    }
    free(model->Mesh);
    model->NumOfMesh = 0;
    free(model->Name);
}

void Face_init(Face *face) {
    face->Point = NULL;
    face->NumFaces = 0;
    face->HasColour = false;
}

void Face_free(Face *face) {
    free(face->Point);
    face->NumFaces = 0;
}

void Vertex_init(Vertex *vertex) {
    vertex->X = 0.0f;
    vertex->Y = 0.0f;
    vertex->Z = 0.0f;
}

Colour Colour_addColourToColour(Colour *firstColour, Colour *secondColour) {
    Colour newColor;
    newColor.RGBA[0] = firstColour->RGBA[0] + secondColour->RGBA[0];
    newColor.RGBA[1] = firstColour->RGBA[1] + secondColour->RGBA[1];
    newColor.RGBA[2] = firstColour->RGBA[2] + secondColour->RGBA[2];
    newColor.RGBA[3] = firstColour->RGBA[3] + secondColour->RGBA[3];
    return newColor;
}

void Colour_NormaliseColour(Colour *colour) {
    float mag = sqrtf((colour->RGBA[0] * colour->RGBA[0]) + (colour->RGBA[1] * colour->RGBA[1]) +
                      (colour->RGBA[2] * colour->RGBA[2]));
    colour->RGBA[0] = colour->RGBA[0] / mag;
    colour->RGBA[1] = colour->RGBA[1] / mag;
    colour->RGBA[2] = colour->RGBA[2] / mag;
}

void Point_init(Point *point) {
    point->VertexID = -1;
    point->TextureID = -1;
    point->NormalID = -1;
}

void Material_init(Material *material) {
    for (size_t i = 0; i < sizeof (material->Ambient); ++i) {
        material->Ambient[i] = 1.0f;
    }
    for (size_t i = 0; i < sizeof (material->Diffuse); ++i) {
        material->Diffuse[i] = 1.0f;
    }
    for (size_t i = 0; i < sizeof (material->Specular); ++i) {
        material->Specular[i] = 1.0f;
    }
    material->OpticalWeight = 1.0f;
    material->DiffuseTexture = NULL;
    material->MaterialName = NULL;
}

int Mesh_findMaterial(Mesh *mesh, char* materialName) {
    for (size_t i = 0; i < mesh->NumOfMaterials; ++i) {
        if (strcmp(materialName, mesh->Materials[i].MaterialName) == 0) {
            return (int)i;
        }
    }
    return -1;
}