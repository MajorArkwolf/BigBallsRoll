#include "model.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Engine/OpenGL.h"

void Mesh_initMesh(Mesh *mesh) {
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
    mesh->Vertices = NULL;
    mesh->Faces = NULL;
}

void Model_draw(Model *model) {
    for (size_t index = 0; index < model->NumOfMesh; ++index) {
        if (model->Mesh[index].Faces[0].NumFaces == 3) {
            glBegin(GL_TRIANGLES);
        } else if (model->Mesh[index].Faces[0].NumFaces == 4) {
            glBegin(GL_QUADS);
        } else if (model->Mesh[index].Faces[0].NumFaces > 4) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINES);
        }

        for (size_t i = 0; i < model->Mesh[index].NumOfFaces; ++i) {
            for (size_t x = 0; x < model->Mesh[index].Faces[i].NumFaces; ++x) {
                size_t index_val = model->Mesh[index].Faces[i].FaceIDs[x];
                if (model->Mesh[index].Vertices[index_val].HasTexture) {
                    //TODO: implement textures here
                }
                if (model->Mesh[index].Faces[i].HasColour) {
                    glColor4f(model->Mesh[index].Faces[i].Colour.RGBA[0], model->Mesh[index].Faces[i].Colour.RGBA[1],
                              model->Mesh[index].Faces[i].Colour.RGBA[2], model->Mesh[index].Faces[i].Colour.RGBA[3]);
                }
                glVertex3f(model->Mesh[index].Vertices[index_val].X, model->Mesh[index].Vertices[index_val].Y, model->Mesh[index].Vertices[index_val].Z);
            }
        }
        glEnd();
    }
}

void Mesh_free(Mesh *mesh) {
    for(size_t i = 0; i < mesh->NumOfFaces; ++i) {
        Face_free(&mesh->Faces[i]);
    }
    free(mesh->Faces);
    free(mesh->Vertices);
    mesh->NumOfFaces = 0;
    mesh->NumOfVert = 0;
}

void Model_initModel(Model *model) {
    model->Name = NULL;
    model->NumOfMesh = 0;
    model->Mesh = NULL;
}

void Model_free(Model *model) {
    for(size_t i = 0; i < model->NumOfMesh; ++i) {
        Mesh_free(&model->Mesh[i]);
    }
    free(model->Mesh);
    model->NumOfMesh = 0;
    free(model->Name);
}

void Face_initFace(Face *face) {
    face->FaceIDs = NULL;
    face->NumFaces = 0;
    face->HasColour = false;
}

void Face_free(Face *face) {
    free(face->FaceIDs);
    face->NumFaces = 0;
}

bool Model_modelToOFF(Model *model) {
    //TODO: Disabled for the time being due to new implementation of Model/Mesh system.
//    FILE *fptr = fopen("./export.off", "w+");
//    if (fptr == NULL) {
//        printf("Failed to create export.off");
//        assert(false);
//        return false;
//    }
//    fputs("OFF\n", fptr);
//    //TODO: word of warning we do not have cells yet implemented.
//    fprintf(fptr, "%zu %zu 0\n", model->NumOfVert, model->NumOfFaces);
//    for (size_t i = 0; i < model->NumOfVert; ++i) {
//        fprintf(fptr, "%f %f %f\n", model->Vertices[i].X, model->Vertices[i].Y, model->Vertices[i].Z);
//    }
//    for (size_t i = 0; i < model->NumOfFaces; ++i) {
//        fprintf(fptr, "%zu ", model->Faces[i].NumFaces);
//        for(size_t x = 0; x < model->Faces[i].NumFaces; ++x) {
//            fprintf(fptr, "%zu ", model->Faces[i].FaceIDs[x]);
//        }
//        if (model->Faces[i].HasColour) {
//            fprintf(fptr, "%f %f %f", model->Faces[i].Colour.RGBA[0], model->Faces[i].Colour.RGBA[1], model->Faces[i].Colour.RGBA[2]);
//        }
//        fprintf(fptr, "\n");
//    }
//    fclose(fptr);
    return true;
}

void Vertex_init(Vertex *vertex) {
    vertex->X = 0.0f;
    vertex->Y = 0.0f;
    vertex->Z = 0.0f;
    vertex->HasTexture = false;
    vertex->HasTexture = false;
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