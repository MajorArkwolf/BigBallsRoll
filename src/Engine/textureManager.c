#define STB_IMAGE_IMPLEMENTATION
#include "textureManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100

void TextureManager_init(TextureManager *textureManager) {
    assert(textureManager != NULL);
    textureManager->NumOfTextures = 0;
}

void TextureManager_free(TextureManager *textureManager) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        free(&textureManager->Textures[i]);
    }
    textureManager->NumOfTextures = 0;
}

//preload textures
void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd) {
    assert(textureManager != NULL);
    //no idea what these do yet
    int width = 0;
    int height = 0;
    int channels = 0;

    char *fulldir = malloc(sizeof(char) * (strlen(cwd) + 30));
    char *imgdir = malloc(sizeof(char) * (strlen(cwd) + 30));

    strcpy(fulldir, cwd);
    strcpy(imgdir, cwd);
    strcpy(imgdir, "res/Texture");
    //No clue about the directory yet
    strcat(fulldir, "res/Loader/textureloading.txt");
    FILE *fptr = fopen(fulldir, "r");
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        textureManager->Textures[textureManager->NumOfTextures].textureName = buff;
        strcpy(imgdir, cwd);
        strcat(imgdir, "res/Texture/");
        strcat(imgdir, buff);
        textureManager->Textures[textureManager->NumOfTextures].textureData = stbi_load(imgdir, &width, &height, &channels, 0);

        if (textureManager->Textures[textureManager->NumOfTextures].textureData != NULL) {
            ++textureManager->NumOfTextures;
        }
    }
    free(fulldir);
}

size_t TextureManager_findTexture(TextureManager *textureManager, char *textureName) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        if(strcmp(textureName, textureManager->Textures[i].textureName) == 0) {
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
