#include "model.h"
#include <stdlib.h>
#include <assert.h>

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
    fprintf(fptr, "%zu %zu %zu\n", model->NumOfVert, model->NumOfFaces, 200ull);
    for (size_t i = 0; i < model->NumOfVert; ++i) {
        fprintf(fptr, "%f %f %f\n", model->Vertices[i].X, model->Vertices[i].Y, model->Vertices[i].Z);
    }
    for (size_t i = 0; i < model->NumOfFaces; ++i) {
        fprintf(fptr, "%zu ", model->Faces[i].NumFaces);
        for(size_t x = 0; x < model->Faces[i].NumFaces; ++x) {
            fprintf(fptr, "%zu ", model->Faces[i].FaceIDs[x]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return true;
}
