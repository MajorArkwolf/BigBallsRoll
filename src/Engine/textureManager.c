//Must be defined before stb_image.h is included
#define STB_IMAGE_IMPLEMENTATION
#include "textureManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100
#define RESOURCE_FILE_LOCATION "res/Texture/"

void TextureManager_init(TextureManager *textureManager) {
    assert(textureManager != NULL);
    textureManager->NumOfTextures = 0;
}

//Not sure if this even works?
void Texture_Free(Texture *texture) {
    assert(texture != NULL);
    free(texture->TextureData);
    texture->TextureName = NULL;
}

void TextureManager_free(TextureManager *textureManager) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        Texture_Free(&textureManager->Textures[i]);
    }
    textureManager->NumOfTextures = 0;
}

//preload textures
void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd) {
    assert(textureManager != NULL);
    //no idea what to do with these yet
    int width = 0;
    int height = 0;
    int channels = 0;

    char *fulldir = malloc(sizeof(char) * (strlen(cwd) + 30));
    char *imgdir = malloc(sizeof(char) * (strlen(cwd) + 30));

    strcpy(fulldir, cwd);
    //No clue about the directory yet
    strcat(fulldir, "res/Loader/textureloading.txt");
    FILE *fptr = fopen(fulldir, "r");
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        if (!TextureManager_isLoaded(textureManager, buff)) {
            textureManager->Textures[textureManager->NumOfTextures].TextureName = calloc(sizeof(char), 50);
            strcpy(textureManager->Textures[textureManager->NumOfTextures].TextureName, buff);
            strcpy(imgdir, cwd);
            strcat(imgdir, RESOURCE_FILE_LOCATION);

            char *fileType = getFileType(buff);
            if (strcmp(fileType, "png") == 0) {
                strcat(imgdir, "PNG/");
            } else if (strcmp(fileType, "jpg") == 0) {
                strcat(imgdir, "JPG/");
            }
            strcat(imgdir, buff);

            textureManager->Textures[textureManager->NumOfTextures].TextureData = stbi_load(imgdir, &width, &height, &channels, 0);

            if (textureManager->Textures[textureManager->NumOfTextures].TextureData != NULL) {
                ++textureManager->NumOfTextures;
            }
        }
    }
    free(fulldir);
    free(imgdir);
    fclose(fptr);
}

void TextureManager_loadTexture(TextureManager *textureManager, char *cwd, char *textureName) {
    assert(textureManager != NULL);

    if (!TextureManager_isLoaded(textureManager, textureName)) {
        int width = 0;
        int height = 0;
        int channels = 0;

        char *imgdir = malloc(sizeof(char) * (strlen(cwd) + 30));
        strcpy(imgdir, cwd);
        strcat(imgdir, RESOURCE_FILE_LOCATION);

        char *fileType = getFileType(textureName);

        printf("\nFiletype: %s", fileType);

        if (strcmp(fileType, "png") == 0) {
            strcat(imgdir, "PNG/");
        } else if (strcmp(fileType, "jpg") == 0) {
            strcat(imgdir, "JPG/");
        }
        strcat(imgdir, textureName);
        textureManager->Textures[textureManager->NumOfTextures].TextureName = textureName;
        textureManager->Textures[textureManager->NumOfTextures].TextureData = stbi_load(imgdir, &width, &height, &channels, 0);

        if (textureManager->Textures[textureManager->NumOfTextures].TextureData != NULL) {
            ++textureManager->NumOfTextures;
        }
        free(imgdir);
    }
}

size_t TextureManager_findTexture(TextureManager *textureManager, char *textureName) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        if(strcmp(textureName, textureManager->Textures[i].TextureName) == 0) {
            return i;
        }
    }
    return 0;
}

Texture* TextureManager_getTexture(TextureManager *textureManager, size_t index) {
    assert(textureManager != NULL);
    if (index >= textureManager->NumOfTextures) {
        printf("Index greater than number of models, return 0 index");
        assert(false);
    }
    return &textureManager->Textures[index];
}

bool TextureManager_isLoaded(TextureManager *textureManager, char*textureName) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        if(strcmp(textureManager->Textures[i].TextureName, textureName) == 0) {
            return true;
        }
    }
    return false;
}

char* getFileType(char *textureName) {
    char *fileType = calloc(sizeof(char), 3);
    fileType[2] = textureName[strlen(textureName)-1];
    fileType[1] = textureName[strlen(textureName)-2];
    fileType[0] = textureName[strlen(textureName)-3];
    return fileType;
}
