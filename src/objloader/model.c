#include "model.h"
#include<stdio.h>

void initModel(Model *model) {
    model->numOfFaces = 0;
    model->numOfVert = 0;
    model->vertices = NULL;
    model->face = NULL;
}