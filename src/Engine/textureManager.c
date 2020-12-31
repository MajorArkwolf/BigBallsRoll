//Must be defined in .c file before stb_image.h is included (dont redefine in any other .c file)
#define STB_IMAGE_IMPLEMENTATION
#include "textureManager.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100
#define RESOURCE_FILE_LOCATION "res/Texture/"
#define DEFAULT_TEXTURE 0

void TextureManager_init(TextureManager *textureManager) {
    assert(textureManager != NULL);
    textureManager->NumOfTextures = 0;
}

//texture->TextureName not freed or set to NULL, else valgrind complains (not sure if its correct)
void Texture_free(Texture *texture) {
    assert(texture != NULL);
    STBI_FREE(texture->TextureData);
}

void TextureManager_free(TextureManager *textureManager) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        Texture_free(&textureManager->Textures[i]);
    }
    textureManager->NumOfTextures = 0;
}

//preload textures
//find out what texture file formats we need, jpg and png are just being used for testing atm
//maybe reconsider if else for filetypes
void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd) {
    assert(textureManager != NULL);
    //no idea what to do with these yet
    int width, height, channels;

    char *fulldir = calloc(sizeof(char), (strlen(cwd) + 100));
    char *imgdir = calloc(sizeof(char), (strlen(cwd) + 100));

    strcpy(fulldir, cwd);
    //No clue about the directory yet
    strcat(fulldir, "res/Loader/textureloading.txt");
    FILE *fptr = fopen(fulldir, "r");
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        if (!TextureManager_isLoaded(textureManager, buff)) {
            textureManager->Textures[textureManager->NumOfTextures].TextureName = calloc(sizeof(char), sizeof(buff) + 30);
            strcpy(textureManager->Textures[textureManager->NumOfTextures].TextureName, buff);
            strcpy(imgdir, cwd);
            strcat(imgdir, RESOURCE_FILE_LOCATION);

            char *fileType = getFileType(buff);
            if (strcmp(fileType, "png") == 0) {
                strcat(imgdir, "PNG/");
            } else if (strcmp(fileType, "jpg") == 0) {
                strcat(imgdir, "JPG/");
            } else if (strcmp(fileType, "bmp") == 0) {
                strcat(imgdir, "BMP/");
            } else {
                printf("\nTexture format not supported: %s", fileType);
                //bad practice using continue here?
                continue;
            }
            strcat(imgdir, buff);

            textureManager->Textures[textureManager->NumOfTextures].TextureData = stbi_load(imgdir, &width, &height, &channels, 0);

            if (textureManager->Textures[textureManager->NumOfTextures].TextureData != NULL) {
                ++textureManager->NumOfTextures;
            }
            free(fileType);
        }
    }
    free(fulldir);
    free(imgdir);
    fclose(fptr);
}
//find more elegant way to deal with freeing
//find out what texture file formats we need, jpg and png are just being used for testing atm
//maybe reconsider if else for filetypes
bool TextureManager_loadTexture(TextureManager *textureManager, char *cwd, char *textureName) {
    assert(textureManager != NULL);

    if (!TextureManager_isLoaded(textureManager, textureName)) {
        int width, height, channels;

        char *imgdir = calloc(sizeof(char), (strlen(cwd) + 100));
        strcpy(imgdir, cwd);
        strcat(imgdir, RESOURCE_FILE_LOCATION);

        char *fileType = getFileType(textureName);

        if (strcmp(fileType, "png") == 0) {
            strcat(imgdir, "PNG/");
        } else if (strcmp(fileType, "jpg") == 0) {
            strcat(imgdir, "JPG/");
        } else if (strcmp(fileType, "bmp") == 0) {
            strcat(imgdir, "BMP/");
        } else {
            printf("\nTexture format not supported: %s", fileType);
            free(imgdir);
            free(fileType);
            return false;
        }
        strcat(imgdir, textureName);
        textureManager->Textures[textureManager->NumOfTextures].TextureName = textureName;
        textureManager->Textures[textureManager->NumOfTextures].TextureData = stbi_load(imgdir, &width, &height, &channels, 0);

        if (textureManager->Textures[textureManager->NumOfTextures].TextureData == NULL) {
            free(imgdir);
            free(fileType);
            return false;
        }
        ++textureManager->NumOfTextures;
        free(imgdir);
        free(fileType);
    }
    return true;
}

Texture* TextureManager_getTexture(TextureManager *textureManager, char *cwd, char *textureName) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        if(strcmp(textureName, textureManager->Textures[i].TextureName) == 0) {
            return &textureManager->Textures[i];
        }
    }
    if (TextureManager_loadTexture(textureManager, cwd, textureName)) {
        return &textureManager->Textures[textureManager->NumOfTextures];
    }
    return &textureManager->Textures[DEFAULT_TEXTURE];
}

Texture* TextureManager_getTextureUsingID(TextureManager *textureManager, size_t index) {
    assert(textureManager != NULL);
    if (index >= textureManager->NumOfTextures) {
        printf("Index greater than number of models, return 0 index");
        return &textureManager->Textures[DEFAULT_TEXTURE];
    }
    return &textureManager->Textures[index];
}

size_t TextureManager_findTextureID(TextureManager *textureManager, char *textureName) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        if(strcmp(textureName, textureManager->Textures[i].TextureName) == 0) {
            return i;
        }
    }
    return DEFAULT_TEXTURE;
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
//not sure on the assert or if it should be handled differently
char* getFileType(char *textureName) {
    assert(textureName != NULL && strlen(textureName) > 3);
    char *fileType = calloc(sizeof(char), 4);
    fileType[2] = textureName[strlen(textureName)-1];
    fileType[1] = textureName[strlen(textureName)-2];
    fileType[0] = textureName[strlen(textureName)-3];
    return fileType;
}
