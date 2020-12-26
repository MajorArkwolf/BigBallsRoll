#include "model.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>

void Model_initModel(Model *model) {
    model->NumOfFaces = 0;
    model->NumOfVert = 0;
    model->Vertices = NULL;
    model->Faces = NULL;
}

void Model_free(Model *model) {
    for(size_t i = 0; i < model->NumOfFaces; ++i) {
        Face_free(&model->Faces[i]);
    }
    free(model->Faces);
    free(model->Vertices);
    model->NumOfFaces = 0;
    model->NumOfVert = 0;
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
    FILE *fptr = fopen("./export.off", "w+");
    if (fptr == NULL) {
        printf("Failed to create export.off");
        assert(false);
        return false;
    }
    fputs("OFF\n", fptr);
    //TODO: word of warning we do not have cells yet implemented.
    fprintf(fptr, "%zu %zu 0\n", model->NumOfVert, model->NumOfFaces);
    for (size_t i = 0; i < model->NumOfVert; ++i) {
        fprintf(fptr, "%f %f %f\n", model->Vertices[i].X, model->Vertices[i].Y, model->Vertices[i].Z);
    }
    for (size_t i = 0; i < model->NumOfFaces; ++i) {
        fprintf(fptr, "%zu ", model->Faces[i].NumFaces);
        for(size_t x = 0; x < model->Faces[i].NumFaces; ++x) {
            fprintf(fptr, "%zu ", model->Faces[i].FaceIDs[x]);
        }
        if (model->Faces[i].HasColour) {
            fprintf(fptr, "%f %f %f", model->Faces[i].Colour.RGBA[0], model->Faces[i].Colour.RGBA[1], model->Faces[i].Colour.RGBA[2]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
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