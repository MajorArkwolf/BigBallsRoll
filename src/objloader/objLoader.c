#include "objLoader.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_MALLOC_SIZE 10000
#define RESOURCE_FILE_LOCATION "res/model/"

size_t countType() {

    return 0;
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

    //TODO: Begin implementing model loading here.

    //Clean up step
    fclose(fptr);
    free(fullDir);
    return model;
}
