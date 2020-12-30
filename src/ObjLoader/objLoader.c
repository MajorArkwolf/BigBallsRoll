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
    fpos_t *meshLocations = NULL;
    size_t amountFound = 0;
    if (!ObjLoader_getMeshLocations(fptr, &meshLocations, &amountFound)) {
        printf("Failed to get meshes.");
        assert(false);
        return false;
    }

    model->Mesh = calloc(amountFound, sizeof (Mesh));

    for (size_t index = 0; index < amountFound; ++index) {
        ObjLoader_loadMesh(&model->Mesh[index], fptr, meshLocations[index]);
    }

    return true;
}


bool ObjLoader_loadMesh(Mesh *mesh, FILE *fptr, fpos_t startLocation) {
//    fsetpos(fptr, &startLocation);
//    char buff[MAX_BUFF_SIZE] = {"\0"};
//    char discard[10];
//    //Verticies
//    size_t v = 0;
//    //Texture Cords
//    size_t vt = 0;
//    //Vertex Normals
//    size_t vp = 0;
//    // Faces
//    size_t f = 0;
//
//    //We need to count what is coming, so this loop is to figure out our memory allocation.
//    while (fgets(buff, sizeof buff, fptr) != NULL) {
//        if (buff[0] == '#') {
//            //Catch and remove any comments.
//            continue;
//        }
//        sscanf(buff, "%4999s", buff);
//        if (strcmp(buff, "v") == 0) { ++v; }
//        if (strcmp(buff, "vt") == 0) { ++vt; }
//        if (strcmp(buff, "vp") == 0) { ++vp; }
//        if (strcmp(buff, "f") == 0) { ++f; }
//    }
//    if (v == 0 || f == 0) {
//        assert(false);
//        return false;
//    }
//    bool result = ModelLoader_allocateMesh(mesh, f, v);
//    if (!result) {
//        assert(false);
//        return result;
//    }
//    fsetpos(fptr, &startLocation);
//
//    while (fgets(buff, sizeof buff, fptr) != NULL) {
//        if (buff[0] == '#') {
//            //Catch and remove any comments.
//            continue;
//        }
//        sscanf(buff, "%9s", discard);
//        if (strcmp(discard, "v") == 0) {
//            assert(v != 0);
//            size_t index = mesh->NumOfVert - v;
//            sscanf(buff, "%9s %f %f %f", discard, &mesh->Vertices[index].X, &mesh->Vertices[index].Y, &mesh->Vertices[index].Z);
//            --v;
//        }
//        if (strcmp(discard, "vt") == 0) {
//            //TODO: Implement this.
//        }
//        if (strcmp(discard, "vp") == 0) {
//            //TODO: Implement this.
//        }
//        if (strcmp(discard, "f") == 0) {
//            assert(f != 0);
//            //Only implemented 3 for now, this may need to be updated later.
//            size_t index = mesh->NumOfFaces - f;
//            mesh->Faces[index].NumFaces = 3;
//            mesh->Faces[index].FaceIDs = calloc(3, sizeof(size_t));
//            sscanf(buff, "%9s %zu %zu %zu", discard, &mesh->Faces[index].FaceIDs[0], &mesh->Faces[index].FaceIDs[1], &mesh->Faces[index].FaceIDs[2]);
//            //Obj's are indexed from 1 not 0, so we must correct the indexing.
//            --mesh->Faces[index].FaceIDs[0];
//            --mesh->Faces[index].FaceIDs[1];
//            --mesh->Faces[index].FaceIDs[2];
//            --f;
//        }
//    }
    return true;
}
