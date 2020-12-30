#define _CRT_SECURE_NO_WARNINGS 1
#include "modelLoader.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Helper/stringPath.h"
#include "objLoader.h"

#define MAX_MALLOC_SIZE 10000
#define MAX_BUFF_SIZE 5000
#define RESOURCE_FILE_LOCATION "res/Model/"

bool ModelLoader_allocateMesh(Mesh *mesh, size_t faces, size_t vertices, size_t textureCords, size_t normals) {
    assert(mesh != NULL);

    //Allocate the required memory for our model then verify it was allocated.
    mesh->Vertices = calloc(vertices, sizeof(Vertex));
    mesh->Faces = calloc(faces, sizeof(Face));
    //Check to see if calloc worked.
    if (mesh->Vertices == NULL || mesh->Faces == NULL) {
        assert(false);
        return false;
    }

    //Once we have confirmed everything worked we set the max values.
    mesh->NumOfFaces = faces;
    mesh->NumOfVert = vertices;
    mesh->NumOfTextureCords = textureCords;
    mesh->NumOfNormals = normals;
    if (textureCords > 0) {
        mesh->TextureCords = malloc(textureCords * sizeof(TextureCord));
    } else {
        mesh->TextureCords = NULL;
    }
    if (normals > 0) {
        mesh->Normals = malloc(normals * sizeof(Vertex));
    } else {
        mesh->Normals = NULL;
    }

    return true;
}

bool ModelLoader_loadOff(Model *model, FILE *fptr) {
    assert(model != NULL && fptr != NULL);
    char buff[MAX_BUFF_SIZE] = {"\0"};
    bool is_configured = false;
    size_t vert = 0, face = 0, cells = 0;

    //OFF only supports a single mesh per OFF file so we hard code it here.
    model->Mesh = malloc(1*sizeof(Mesh));
    if (model->Mesh == NULL) {
        printf("Calloc failed when making Mesh in loadOff");
        assert(false);
        return false;
    }
    model->NumOfMesh = 1;

    while (fgets(buff, sizeof buff, fptr) != NULL) {
        // We ignore anything that is a comment or a header declaring OFF.
        if (buff[0] == '#' || (buff[0] == 'O' && buff[1] == 'F' && buff[2] == 'F')) {
            continue;
        }
        //Next we check if the declared values are specified.
        if (!is_configured) {
            if (sscanf(buff, "%zu %zu %zu", &vert, &face, &cells) != 3) {
                assert(false);
                return false;
            }
            if (vert == 0 || face == 0) {
                return false;
            }
            ModelLoader_allocateMesh(&model->Mesh[0], face, vert, 0, 0);
            is_configured = true;
        } else {
            if (vert != 0) {
                size_t index = model->Mesh[0].NumOfVert - vert;
                sscanf(buff, "%f %f %f", &model->Mesh[0].Vertices[index].X, &model->Mesh[0].Vertices[index].Y,
                       &model->Mesh[0].Vertices[index].Z);
                --vert;
            } else if (face != 0) {
                size_t index = model->Mesh[0].NumOfFaces - face;
                size_t numPerRow = 0;
                char *data = buff;
                int offset;

                sscanf(buff, "%zu%n", &numPerRow, &offset);
                data += offset;
                Face_init(&model->Mesh[0].Faces[index]);
                model->Mesh[0].Faces[index].Point = calloc(numPerRow, sizeof(Point));
                if (model->Mesh[0].Faces[index].Point == NULL) {
                    printf("Failed to allocate ID's for faces");
                    assert(false);
                    return false;
                }
                model->Mesh[0].Faces[index].NumFaces = numPerRow;

                for (size_t i = 0; i < numPerRow; ++i) {
                    Point_init(&model->Mesh[0].Faces[index].Point[i]);
                    sscanf(data, "%d%n", &model->Mesh[0].Faces[index].Point[i].VertexID, &offset);
                    data += offset;
                }
                //Process colour
                Colour colour;
                int n = sscanf(data, "%f %f %f %f", &colour.RGBA[0], &colour.RGBA[1], &colour.RGBA[2], &colour.RGBA[3]);
                if (n >= 3) {
                    if (n != 4) {
                        colour.RGBA[3] = 1;
                    }
                    model->Mesh[0].Faces[index].HasColour = true;
                    model->Mesh[0].Faces[index].Colour = colour;
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

    for (size_t i = 0; i < model->Mesh[0].NumOfFaces; ++i) {
        Colour_NormaliseColour(&model->Mesh[0].Faces[i].Colour);
    }

    return true;
}

Model ModelLoader_loadModel(char *workingDir, char *fileName) {
    //Get the full directory to our model.
    bool modelLoaded = false;
    char *fullDir = malloc(MAX_MALLOC_SIZE * sizeof(char));
    strcpy(fullDir, workingDir);
    strcat(fullDir, RESOURCE_FILE_LOCATION);
    strcat(fullDir, fileName);

    Model model;
    Model_init(&model);
    model.Name = malloc(strlen(fileName) * sizeof(char) + 1);
    strcpy(model.Name, fileName);
    FILE *fptr;
    fptr = fopen(fullDir, "r");
    //Failed to open a file with the given name.
    assert(fptr != NULL);
    // Send of to the appropriate loader
    char *ext = getFileTypeFromPath(fullDir);
    if (strcmp(ext, "off") == 0) {
        modelLoaded = ModelLoader_loadOff(&model, fptr);
    } else if (strcmp(ext, "obj") == 0) {
        modelLoaded = ObjLoader_loadObj(&model, fptr);
    }
    free(ext);
    if (!modelLoaded) {
        printf("Model failed to load.");
        assert(false);
    }

    //Clean up step
    fclose(fptr);
    free(fullDir);
    return model;
}
