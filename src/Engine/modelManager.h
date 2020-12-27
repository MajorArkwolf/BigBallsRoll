#pragma once
#include "ObjLoader/model.h"
#define MAX_MODELS 1000

typedef struct ModelManager{
    size_t NumOfModels;
    Model Models[MAX_MODELS];
} ModelManager;

void ModelManager_init(ModelManager *modelManger);

void ModelManager_free(ModelManager *modelManger);

void ModelManager_loadModels(ModelManager *modelManger, char* cwd);

size_t ModelManager_findModel(ModelManager *modelManger, char *modelName);

Model* ModelManager_getModel(ModelManager *modelManger, size_t index);
