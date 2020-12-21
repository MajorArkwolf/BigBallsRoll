#include "objLoader.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Helper/stringPath.h"

#define MAX_MALLOC_SIZE 10000
#define RESOURCE_FILE_LOCATION "res/model/"

bool loadOff(Model *model, FILE *fptr) {

    return true;
}

size_t countType() {

    return 0;
}

bool loadObj(Model *model, FILE *fptr) {

    return true;
}

Model loadModel(char *workingDir, char *fileName) {
    //Get the full directory to our model.
    char *fullDir = malloc(MAX_MALLOC_SIZE * sizeof(char));
    strcpy(fullDir, workingDir);
    strcat(fullDir, RESOURCE_FILE_LOCATION);
    strcat(fullDir, fileName);

    Model model;
    initModel(&model);

    FILE *fptr;
    fptr = fopen(fullDir, "r");
    if (fptr == NULL) {
        //Failed to open a file with the given name.
        assert(false);
    }

    //Find the type of model we will be using and send to the appropriate function.
    char *fileType = getFileTypeFromPath(fullDir);
    if (strcmp(fileType, "off") == 0) {
        assert(loadOff(&model, fptr));
    } else if (strcmp(fileType, "obj") == 0) {
        assert(loadObj(&model, fptr));
    } else {
        assert(false);
    }

    //Clean up step
    fclose(fptr);
    //free(fileType);
    free(fullDir);
    return model;
}
