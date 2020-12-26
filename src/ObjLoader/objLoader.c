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

bool AllocateModel(Model *model, size_t faces, size_t vertices) {
    //TODO: Possibly at a precheck to ensure the model is null.

    //Allocate the required memory for our model then verify it was allocated.
    model->Vertices = calloc(vertices, sizeof(Vertex));
    model->Faces = calloc(faces, sizeof(Face));
    //Check to see if calloc worked.
    if (model->Vertices == NULL || model->Faces == NULL) {
        assert(false);
        return false;
    }

    //Once we have confirmed everything worked we set the max values.
    model->NumOfFaces = faces;
    model->NumOfVert = vertices;

    return true;
}

bool loadOff(Model *model, FILE *fptr) {
    assert(model != NULL && fptr != NULL);
    char buff[MAX_BUFF_SIZE] = {"\0"};
    bool is_configured = false;
    size_t vert = 0, face = 0, cells = 0;
    while (fgets(buff, sizeof buff, fptr) != NULL) {
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
            if (vert == 0 || face == 0) {
                return false;
            }
            AllocateModel(model, face, vert);
            is_configured = true;
        } else {
            if (vert != 0) {
                size_t index = model->NumOfVert - vert;
                sscanf(buff, "%f %f %f", &model->Vertices[index].X, &model->Vertices[index].Y,
                       &model->Vertices[index].Z);
                --vert;
            } else if (face != 0) {
                size_t index = model->NumOfFaces - face;
                size_t numPerRow = 0;
                char *data = buff;
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
    char buff[MAX_BUFF_SIZE] = {"\0"};
    char discard[10];
    //Verticies
    size_t v = 0;
    //Texture Cords
    size_t vt = 0;
    //Vertex Normals
    size_t vp = 0;
    // Faces
    size_t f = 0;

    //We need to count what is coming, so this loop is to figure out our memory allocation.
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (buff[0] == '#') {
            //Catch and remove any comments.
            continue;
        }
        sscanf(buff, "%MAX_BUFF_SIZEs", buff);
        if (strcmp(buff, "v") == 0) { ++v; }
        if (strcmp(buff, "vt") == 0) { ++vt; }
        if (strcmp(buff, "vp") == 0) { ++vp; }
        if (strcmp(buff, "f") == 0) { ++f; }
    }
    if (v == 0 || f == 0) {
        assert(false);
        return false;
    }
    bool result = AllocateModel(model, f, v);
    if (!result) {
        assert(false);
        return result;
    }
    rewind(fptr);

    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (buff[0] == '#') {
            //Catch and remove any comments.
            continue;
        }
        sscanf(buff, "%10s", discard);
        if (strcmp(discard, "v") == 0) {
            assert(v != 0);
            size_t index = model->NumOfVert - v;
            sscanf(buff, "%10s %f %f %f", discard, &model->Vertices[index].X, &model->Vertices[index].Y, &model->Vertices[index].Z);
            --v;
        }
        if (strcmp(discard, "vt") == 0) {
            //TODO: Implement this.
        }
        if (strcmp(discard, "vp") == 0) {
            //TODO: Implement this.
        }
        if (strcmp(discard, "f") == 0) {
            assert(f != 0);
            //Only implemented 3 for now, this may need to be updated later.
            size_t index = model->NumOfFaces - f;
            model->Faces[index].NumFaces = 3;
            model->Faces[index].FaceIDs = calloc(3, sizeof(size_t));
            sscanf(buff, "%10s %zu %zu %zu", discard, &model->Faces[index].FaceIDs[0], &model->Faces[index].FaceIDs[1], &model->Faces[index].FaceIDs[2]);
            //Obj's are indexed from 1 not 0, so we must correct the indexing.
            --model->Faces[index].FaceIDs[0];
            --model->Faces[index].FaceIDs[1];
            --model->Faces[index].FaceIDs[2];
            --f;
        }
    }
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
