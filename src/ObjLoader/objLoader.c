#define _CRT_SECURE_NO_WARNINGS 1

#include "objLoader.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ObjLoader/modelLoader.h"

#define MAX_BUFF_SIZE 5000

bool ObjLoader_getMeshLocations(FILE *fptr, fpos_t **location, size_t *amountFound) {
//    assert(*location == NULL && amountFound != NULL);
//    char buff[MAX_BUFF_SIZE];
//    while (fgets(buff, sizeof(buff), fptr) != NULL) {
//        if (buff[0] == 'g') {
//            ++*amountFound;
//        }
//    }
//    rewind(fptr);
//    //If no g tag is found then its safe to assume its a single mesh model.
//    if (*amountFound == 0) {
//        *amountFound = 1ul;
//    }
//    *location = malloc(*amountFound * sizeof (fpos_t));
//    if (*location == NULL) {
//        printf("calloc failed in ObjLoader_getMeshLocations");
//        assert(false);
//        return false;
//    }
//    if (*amountFound == 1) {
//        *location[0] = ftell(fptr);
//        return true;
//    }
//
//    size_t index = 0;
//    while (1) {
//        fpos_t temp = ftell(fptr);
//        if (fgets(buff, sizeof(buff), fptr) == NULL) {
//            break;
//        }
//        if (buff[0] == 'g') {
//            location[0][index] = temp;
//            ++index;
//        }
//    }
    return true;
}


bool ObjLoader_loadObj(Model *model, FILE *fptr) {
    model->Mesh = malloc(1*sizeof(Mesh));
    if (model->Mesh == NULL) {
        printf("malloc failed when making Mesh in loadOff");
        assert(false);
        return false;
    }
    model->NumOfMesh = 1;
    ObjLoader_loadMesh(&model->Mesh[0], fptr);
    return true;
}

void ObjLoader_addPointData(Point *point, char* string, size_t slashCount) {
    if (slashCount == 0) {
        //this is a vertex id
        point->VertexID = atoi(string);
        --point->VertexID;
    } else if (slashCount == 1) {
        //this is a texture cord
        point->TextureID = atoi(string);
    } else if (slashCount == 2) {
        // this is a normal
        point->NormalID = atoi(string);
    }
}

bool ObjLoader_loadMesh(Mesh *mesh, FILE *fptr) {
    rewind(fptr);
    char buff[MAX_BUFF_SIZE] = {"\0"};
    char discard[10];
    size_t index = 0;
    //Verticies
    size_t v = 0;
    //Texture Cords
    size_t vt = 0;
    //Vertex Normals
    size_t vn = 0;
    // Faces
    size_t f = 0;

    //We need to count what is coming, so this loop is to figure out our memory allocation.
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (buff[0] == '#') {
            //Catch and remove any comments.
            continue;
        }
        sscanf(buff, "%4999s", buff);
        if (strcmp(buff, "v") == 0) { ++v; }
        if (strcmp(buff, "vt") == 0) { ++vt; }
        if (strcmp(buff, "vn") == 0) { ++vn; }
        if (strcmp(buff, "f") == 0) { ++f; }
    }
    if (v == 0 || f == 0) {
        assert(false);
        return false;
    }
    bool result = ModelLoader_allocateMesh(mesh, f, v, vt, vn);
    if (!result) {
        assert(false);
        return result;
    }
    rewind(fptr);

    //Verticies
    size_t vCount = 0;
    //Texture Cords
    size_t vtCount = 0;
    //Vertex Normals
    size_t vnCount = 0;
    // Faces
    size_t fCount = 0;

    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (buff[0] == '#') {
            //Catch and remove any comments.
            continue;
        }
        sscanf(buff, "%9s", discard);
        if (strcmp(discard, "v") == 0) {
            index = vCount;
            sscanf(buff, "%9s %f %f %f", discard, &mesh->Vertices[index].X, &mesh->Vertices[index].Y,
                   &mesh->Vertices[index].Z);
            ++vCount;
            continue;
        }
        if (strcmp(discard, "vt") == 0) {
            index = vtCount;
            sscanf(buff, "%9s %f %f", discard, &mesh->TextureCords[index].T[0], &mesh->TextureCords[index].T[1]);
            ++vtCount;
            continue;
        }
        if (strcmp(discard, "vn") == 0) {
            index = vnCount;
            sscanf(buff, "%9s %f %f %f", discard, &mesh->Normals[index].X, &mesh->Normals[index].Y,
                   &mesh->Normals[index].Z);
            ++vnCount;
            continue;
        }
        if (strcmp(discard, "f") == 0) {
            index = fCount;
            Face_init(&mesh->Faces[index]);
            Point point[10];
            size_t numOfFaces = 0;
            size_t slashCount = 0;
            char *pntr = NULL;
            size_t indexIncrement = 0;
            Point_init(&point[0]);
            for (size_t i = 2; i < strlen(buff); ++i) {
                if (buff[i] == '\0' || buff[i] == '\n') {
                    ObjLoader_addPointData(&point[numOfFaces], pntr, slashCount);
                    ++numOfFaces;
                    break;
                } else if (buff[i] == '/') {
                    ObjLoader_addPointData(&point[numOfFaces], pntr, slashCount);
                    //Convert to value;
                    indexIncrement = 0;
                    pntr = NULL;
                    ++slashCount;
                    continue;
                } else if (buff[i] == ' ') {
                    ObjLoader_addPointData(&point[numOfFaces], pntr, slashCount);
                    ++numOfFaces;
                    Point_init(&point[numOfFaces]);
                    //Convert to value;
                    indexIncrement = 0;
                    pntr = NULL;
                    slashCount = 0;
                    continue;
                } else if (buff[i] >= '0' && buff[i] <= '9') {
                    if (pntr == NULL) {
                        pntr = &buff[i];
                    }
                    ++indexIncrement;
                }
            }
            mesh->Faces[index].NumFaces = numOfFaces;
            mesh->Faces[index].Point = calloc(numOfFaces, sizeof(Point));
            for (size_t i = 0; i < numOfFaces; ++i) {
                mesh->Faces[index].Point[i] = point[i];
            }
            ++fCount;
        }
    }
    return true;
}
