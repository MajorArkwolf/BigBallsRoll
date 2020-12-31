#define _CRT_SECURE_NO_WARNINGS 1

#include "objLoader.h"

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Engine/engine.h"
#include "ObjLoader/modelLoader.h"

#define MAX_BUFF_SIZE 5000

bool ObjLoader_loadMTL(Mesh *mesh, char *dir) {
    //Attempt to open the MTL file.
    FILE *fptr = fopen(dir, "r");
    if (fptr == NULL) {
        printf("Failed to open MTL: %s\n", dir);
        assert(false);
        return false;
    }
    //Next we check how many materials we have.
    char buff[MAX_BUFF_SIZE];
    char discard[10] = {'\0'};
    size_t numOfMaterials = 0;
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        sscanf(buff, "%9s", discard);
        if (strcmp(discard, "newmtl") == 0) {
            ++numOfMaterials;
        }
    }

    //Allocate Materials to be used in the project.
    mesh->Materials = malloc(numOfMaterials * sizeof(Material));
    if (mesh->Materials == NULL) {
        printf("Failed to allocate Mesh for %s.\n", dir);
        assert(false);
        return false;
    }
    mesh->NumOfMaterials = numOfMaterials;
    //We reset this back to zero to be used for indexing later.
    int index = -1;
    rewind(fptr);
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        sscanf(buff, "%9s", discard);
        if (strcmp(discard, "newmtl") == 0) {
            char smallBuff[1000];
            ++index;
            Material_init(&mesh->Materials[index]);
            sscanf(buff, "%9s %4999s", discard, smallBuff);
            mesh->Materials[index].MaterialName = malloc(1000 * sizeof(char));
            strcpy(mesh->Materials[index].MaterialName, smallBuff);
            continue;
        }
        if (index == -1) {
            printf("Failed to find first material, aborting");
            assert(false);
            return false;
        }
        if (strcmp(discard, "Kd") == 0) {
            sscanf(buff, "%s %f %f %f", discard, &mesh->Materials[index].Diffuse[0], &mesh->Materials[index].Diffuse[1], &mesh->Materials[index].Diffuse[2]);
            continue;
        }
        if (strcmp(discard, "Ka") == 0) {
            sscanf(buff, "%s %f %f %f", discard, &mesh->Materials[index].Ambient[0], &mesh->Materials[index].Ambient[1], &mesh->Materials[index].Ambient[2]);
            continue;
        }
        if (strcmp(discard, "Tf") == 0) {
            //TODO: Not implemented yet.
        }
        if (strcmp(discard, "Ni") == 0) {
            sscanf(buff, "%s %f", discard, &mesh->Materials[index].OpticalWeight);
            continue;
        }
        if (strcmp(discard, "map_Kd") == 0) {
            char textureFile[MAX_BUFF_SIZE] = {'\0'};
            sscanf(buff, "%s %s", discard, textureFile);
            mesh->Materials[index].DiffuseTexture = TextureManager_getTexture(&engine.textureManager, engine.cwd, textureFile);
        }
    }

    fclose(fptr);
    return true;
}

bool ObjLoader_loadObj(Model *model, FILE *fptr, char *cwd) {
    model->Mesh = malloc(1 * sizeof(Mesh));
    if (model->Mesh == NULL) {
        printf("malloc failed when making Mesh in loadOff");
        assert(false);
        return false;
    }
    model->NumOfMesh = 1;
    Mesh_init(&model->Mesh[0]);
    ObjLoader_loadMesh(&model->Mesh[0], fptr, cwd);
    return true;
}

void ObjLoader_addPointData(Point *point, char *value, size_t slashCount) {
    if (slashCount == 0) {
        //this is a vertex id
        point->VertexID = atoi(value);
        --point->VertexID;
    } else if (slashCount == 1) {
        //this is a texture cord
        point->TextureID = atoi(value);
        --point->TextureID;
    } else if (slashCount == 2) {
        // this is a normal
        point->NormalID = atoi(value);
        --point->NormalID;
    }
}

bool ObjLoader_loadMesh(Mesh *mesh, FILE *fptr, char *cwd) {
    rewind(fptr);
    char buff[MAX_BUFF_SIZE] = {"\0"};
    char discard[10] = {'\0'};
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
        sscanf(buff, "%9s", discard);
        if (strcmp(discard, "v") == 0) {
            ++v;
        }
        if (strcmp(discard, "vt") == 0) {
            ++vt;
        }
        if (strcmp(discard, "vn") == 0) {
            ++vn;
        }
        if (strcmp(discard, "f") == 0) {
            ++f;
        }
        if (strcmp(discard, "mtllib") == 0) {
            char mtlFile[1000];
            sscanf(buff, "%s %s", discard, mtlFile);
            strcat(cwd, mtlFile);
            ObjLoader_loadMTL(mesh, cwd);
            assert(mesh->NumOfMaterials != 0);
        }
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
    //The current bound mtl
    int activeMTL = -1;
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (buff[0] == '#') {
            //Catch and remove any comments.
            continue;
        }
        sscanf(buff, "%9s", discard);
        if (strcmp(discard, "usemtl") == 0) {
            sscanf(buff, "%9s %s", discard, buff);
            activeMTL = Mesh_findMaterial(mesh, buff);
        }
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
            if (f <= fCount) { continue; }
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
            mesh->Faces[index].Point = malloc(numOfFaces * sizeof(Point));
            mesh->Faces[index].MaterialIndex = activeMTL;
            for (size_t i = 0; i < numOfFaces; ++i) {
                mesh->Faces[index].Point[i] = point[i];
            }
            ++fCount;
        }
    }
    return true;
}
