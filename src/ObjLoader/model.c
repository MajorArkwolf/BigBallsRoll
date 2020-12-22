#include "model.h"
#include <stdlib.h>

void model_initModel(Model *model) {
    model->NumOfFaces = 0;
    model->NumOfVert = 0;
    model->Vertices = NULL;
    model->Faces = NULL;
}

void model_free(Model *model) {
    free(model->Faces);
    free(model->Vertices);
    model->NumOfFaces = 0;
    model->NumOfVert = 0;
}