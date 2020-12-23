#include "objLoader.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Helper/stringPath.h"

#define MAX_MALLOC_SIZE 10000
#define MAX_BUFF_SIZE 5000
#define RESOURCE_FILE_LOCATION "res/model/"
#define _CRT_SECURE_NO_WARNINGS

size_t countType() {

    return 0;
}

bool loadOff(Model *model, FILE *fptr) {
    char buff[MAX_BUFF_SIZE] = {"\0"};
    bool is_configured = false;
    size_t vert = 0, face = 0, cells = 0, count = 0;
    while(fgets(buff, sizeof buff, fptr) != NULL) {
        // We ignore anything that is a comment or a header declaring OFF.
        if (buff[0] == '#' || (buff[0] == 'O' && buff[1] == 'F' && buff[2] == 'F')) {
            continue;
        }
        //Next we check if the declared values are specified.
        if (!is_configured) {
            if (sscanf(buff, "%zu %zu %zu", &vert, &face, &cells) <= 0) {
                assert(false);
                return false;
            }
            if (vert < 0 || face < 0) {
                return false;
            }
            //Allocate the required memory for our model then verify it was allocated.
            model->Vertices = malloc(vert * sizeof(Vertex));
            model->Faces = malloc(face * sizeof(Face));
            if (model->Vertices == NULL || model->Faces == NULL) {
                assert(false);
                return false;
            }
            //Once we have confirmed everything worked we set the max values.
            model->NumOfFaces = face;
            model->NumOfVert = vert;
            is_configured = true;
        } else {
            if (vert != 0) {
                size_t index = model->NumOfVert - vert;
                sscanf(buff, "%f %f %f", &model->Vertices[index].X, &model->Vertices[index].Y, &model->Vertices[index].Z);
                --vert;
            } else if (face != 0) {
                size_t index = model->NumOfFaces - face;
                size_t numPerRow = 0;
                char* data = buff;
                int offset;

                sscanf(buff, "%zu%n", &numPerRow, &offset);
                data += offset;
                Face_initFace(&model->Faces[index]);
                model->Faces[index].FaceIDs = calloc(numPerRow, sizeof(size_t));
                if (model->Faces[index].FaceIDs == NULL) {
                    printf("Failed to allocate ID's for faces");
                    assert(false);
                    return false;
                }
                model->Faces[index].NumFaces = numPerRow;

                for (size_t i = 0; i < numPerRow; ++i) {
                    sscanf(data, "%zu%n", &model->Faces[index].FaceIDs[i], &offset);
                    data += offset;
                }
                --face;
            } else if (cells != 0) {
                //TODO: Not yet implemented
                cells = 0;
                //--cells;
            } else {
                break;
            }
        }
    }
    return true;
}

bool loadObj(Model *model, FILE *fptr) {
    return true;
}

Model loadModel(char *workingDir, char *fileName) {
    //Get the full directory to our model.
    bool modelLoaded = false;
    char *fullDir = malloc(MAX_MALLOC_SIZE * sizeof(char));
    strcpy(fullDir, workingDir);
    strcat(fullDir, RESOURCE_FILE_LOCATION);
    strcat(fullDir, fileName);

    Model model;
    Model_initModel(&model);

    FILE *fptr;
    fptr = fopen(fullDir, "r");
    //Failed to open a file with the given name.
    assert(fptr != NULL);

    //TODO: Begin implementing model loading here.
    char *ext = getFileTypeFromPath(fullDir);
    if (strcmp(ext, "off") == 0) {
        modelLoaded = loadOff(&model, fptr);
    } else if (strcmp(ext, "obj") == 0) {
        modelLoaded = loadObj(&model, fptr);
    }

    if (!modelLoaded) {
        printf("Model failed to load.");
        assert(false);
    }

    //Clean up step
    fclose(fptr);
    free(fullDir);
    return model;
}
