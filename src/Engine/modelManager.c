#include "modelManager.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ObjLoader/objLoader.h"
#include "ObjLoader/model.h"
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100

void ModelManager_init(ModelManager *modelManger) {
    assert(modelManger != NULL);
    modelManger->NumOfModels = 0;
}

void ModelManager_free(ModelManager *modelManger) {
    assert(modelManger != NULL);
    for (size_t i = 0; i < modelManger->NumOfModels; ++i) {
        Model_free(&modelManger->Models[i]);
    }
    modelManger->NumOfModels = 0;
}

void ModelManager_loadModels(ModelManager *modelManger, char *cwd) {
    assert(modelManger != NULL);
    char *fulldir = malloc(sizeof(char) * (strlen(cwd) + 30));
    strcpy(fulldir, cwd);
    strcat(fulldir, "res/Loader/modelloading.txt");
    FILE *fptr = fopen(fulldir, "r");
    assert(fptr != NULL);
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        modelManger->Models[modelManger->NumOfModels] = ObjLoader_loadModel(cwd, buff);
        ++modelManger->NumOfModels;
    }
    free(fulldir);
}

size_t ModelManager_findModel(ModelManager *modelManger, char *modelName) {
    assert(modelManger != NULL);
    for (size_t i = 0; i < modelManger->NumOfModels; ++i) {
        if (strcmp(modelName, modelManger->Models[i].Name) == 0) {
            return i;
        }
    }
    return 0;
}

Model* ModelManager_getModel(ModelManager *modelManger, size_t index) {
    assert(modelManger != NULL);
    if (index > modelManger->NumOfModels) {
        printf("Index greater then number of models, return 0 index");
        assert(false);
        return &modelManger->Models[0];
    }
    return &modelManger->Models[index];
}