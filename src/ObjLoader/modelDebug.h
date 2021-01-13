#pragma once
#include "ObjLoader/model.h"

bool modelToOFF(Model *model) {
    FILE *fptr = fopen("./export.off", "w+");
    if (fptr == NULL) {
        printf("Failed to create export.off");
        assert(false);
        return false;
    }
    fputs("OFF\n", fptr);
    //TODO: word of warning we do not have cells yet implemented.
    fprintf(fptr, "%zu %zu 0\n", model->Mesh->NumOfVert, model->Mesh->NumOfFaces);
    for (size_t i = 0; i < model->Mesh->NumOfVert; ++i) {
        fprintf(fptr, "%f %f %f\n", model->Mesh->Vertices[i].X, model->Mesh->Vertices[i].Y, model->Mesh->Vertices[i].Z);
    }
    for (size_t i = 0; i < model->Mesh->NumOfFaces; ++i) {
        fprintf(fptr, "%zu ", model->Mesh->Faces[i].NumFaces);
        for(size_t x = 0; x < model->Mesh->Faces[i].NumFaces; ++x) {
            fprintf(fptr, "%d ", model->Mesh->Faces[i].Point[x].VertexID);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return true;
}
