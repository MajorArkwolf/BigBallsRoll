#include "model.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Engine/OpenGL.h"

void Mesh_init(Mesh *mesh) {
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
    mesh->NumOfMaterials = 0;
    mesh->NumOfTextureCords = 0;
    mesh->NumOfNormals = 0;
    mesh->Vertices = NULL;
    mesh->Faces = NULL;
    mesh->Materials = NULL;
    mesh->TextureCords = NULL;
    mesh->Normals = NULL;
}

void Model_draw(Model *model) {
    int lastTexture = GL_NONE;
    glColor3f(1, 1, 1);
    for (size_t index = 0; index < model->NumOfMesh; ++index) {
        for (size_t i = 0; i < model->Mesh[index].NumOfFaces; ++i) {

            int matIndex = model->Mesh[index].Faces[i].MaterialIndex;
            if (matIndex >= 0 && model->Mesh[index].Materials != NULL && model->Mesh[index].Materials[matIndex].DiffuseTexture != NULL) {
                if (lastTexture != model->Mesh[index].Materials[matIndex].DiffuseTexture->GLTextureID) {
                    lastTexture = (int)model->Mesh[index].Materials[matIndex].DiffuseTexture->GLTextureID;
                    //TODO: this is broken and hardcoded, this is for testing purposes only.
                }
            }
            glBindTexture(GL_TEXTURE_2D, lastTexture);
            glBegin(GL_POLYGON);
            for (size_t x = 0; x < model->Mesh[index].Faces[i].NumFaces; ++x) {
                int textureIndex = model->Mesh[index].Faces[i].Point[x].TextureID;
                if (model->Mesh->NumOfTextureCords > textureIndex) {
                    float t1 = model->Mesh[index].TextureCords[textureIndex].T[0];
                    float t2 = model->Mesh[index].TextureCords[textureIndex].T[1];
                    glTexCoord2f(t1, t2);
                }
                int index_val = model->Mesh[index].Faces[i].Point[x].VertexID;
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
    free(mesh->Materials);
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
    mesh->NumOfMaterials = 0;
    mesh->NumOfTextureCords = 0;
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
    face->MaterialIndex = -1;
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
    float mag = sqrtf((colour->RGBA[0] * colour->RGBA[0]) + (colour->RGBA[1] * colour->RGBA[1]) + (colour->RGBA[2] * colour->RGBA[2]));
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
    for (size_t i = 0; i < 3; ++i) {
        material->Ambient[i] = 1.0f;
    }
    for (size_t i = 0; i < 3; ++i) {
        material->Diffuse[i] = 1.0f;
    }
    for (size_t i = 0; i < 3; ++i) {
        material->Specular[i] = 1.0f;
    }
    material->OpticalWeight = 1.0f;
    material->DiffuseTexture = NULL;
    material->MaterialName = NULL;
}

int Mesh_findMaterial(Mesh *mesh, char *materialName) {
    for (size_t i = 0; i < mesh->NumOfMaterials; ++i) {
        if (strcmp(materialName, mesh->Materials[i].MaterialName) == 0) {
            return (int) i;
        }
    }
    return -1;
}
