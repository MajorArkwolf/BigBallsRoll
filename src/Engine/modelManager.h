#pragma once
#include "ObjLoader/model.h"

/// Arbitrary amount of models, this keeps our models on the stack so we can have faster access to them.
#define MAX_MODELS 1000

/// Model Manager Structure
typedef struct ModelManager{
    Model Models[MAX_MODELS];
    size_t NumOfModels;
    char *cwd;
} ModelManager;

/**
 * Initialises model manager, must be allocated prior to being used
 * @param modelManger object to initialise
 */
void ModelManager_init(ModelManager *modelManger);

/**
 * Free objects contained inside of the Model Manager
 * @param modelManger Model Manager to be free its contents
 */
void ModelManager_free(ModelManager *modelManger);

/**
 * Loads models that are declared in res/Loader/modelloading.txt to be used later
 * @param modelManger Model Manager to be load models into
 * @param cwd the current working directory, must contain res folder to work
 */
void ModelManager_loadModels(ModelManager *modelManger, char* cwd);

/**
 * Find a model based off its relevant path from the res folder and return the index id to it
 * @param modelManger model manager to search in
 * @param modelName string name to look up
 * @return the id of where it exists in the array, 0 if not found.
 */
size_t ModelManager_findModel(ModelManager *modelManger, char *modelName);

/**
 * Return a model based of the index value.
 * @param modelManger modelManger model manager to search in
 * @param index value of where the model exists in the array
 * @return return the model or return model 0 if the index is out of bounds
 */
Model* ModelManager_getModel(ModelManager *modelManger, size_t index);
