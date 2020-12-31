//Must be defined in .c file before stb_image.h is included (dont redefine in any other .c file)
#define STB_IMAGE_IMPLEMENTATION
#include "textureManager.h"
#include "Engine/OpenGL.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100
#define RESOURCE_FILE_LOCATION "res/Texture/"
#define RESOURCE_LOADER_FILE_LOCATION "res/Loader/textureloading.txt"
#define DEFAULT_TEXTURE 0

void TextureManager_bindTextureOpenGL(Texture *texture) {
    glGenTextures(1, &texture->GLTextureID);
    glBindTexture(GL_TEXTURE_2D, texture->GLTextureID);
    unsigned colouChannel = GL_RGB;
    if (texture->Channels == 4) {
        colouChannel = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, texture->Channels, texture->Width, texture->Height, 0, colouChannel, GL_UNSIGNED_BYTE, texture->TextureData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
}

void TextureManager_init(TextureManager *textureManager) {
    assert(textureManager != NULL);
    textureManager->NumOfTextures = 0;
}

void Texture_init(Texture *texture) {
    assert(texture != NULL);
    //texture->TextureName = {"\0"};
    texture->TextureData = NULL;
    texture->Width = 0;
    texture->Height = 0;
    texture->Channels = 0;
    texture->GLTextureID = 0;
}

void Texture_free(Texture *texture) {
    assert(texture != NULL);
    STBI_FREE(texture->TextureData);
    free(texture->TextureName);
    texture->Width = 0;
    texture->Height = 0;
    texture ->Channels = 0;
}

void TextureManager_free(TextureManager *textureManager) {
    assert(textureManager != NULL);
    for (size_t i = 0; i < textureManager->NumOfTextures; ++i) {
        Texture_free(&textureManager->Textures[i]);
    }
    textureManager->NumOfTextures = 0;
}

//Pre-load textures
void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd) {
    assert(textureManager != NULL);

    const int DesiredChannels = 0;
    char *fulldir = calloc(sizeof(char), (strlen(cwd) + 100));
    char *imgdir = calloc(sizeof(char), (strlen(cwd) + 100));

    strcpy(fulldir, cwd);
    strcat(fulldir, RESOURCE_LOADER_FILE_LOCATION);
    FILE *fptr = fopen(fulldir, "r");
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        if (!TextureManager_isLoaded(textureManager, buff)) {
            Texture_init(&textureManager->Textures[textureManager->NumOfTextures]);
            strcpy(textureManager->Textures[textureManager->NumOfTextures].TextureName, buff);
            strcpy(imgdir, cwd);
            strcat(imgdir, RESOURCE_FILE_LOCATION);
            strcat(imgdir, buff);

            textureManager->Textures[textureManager->NumOfTextures].TextureData =
                    stbi_load(imgdir, &textureManager->Textures[textureManager->NumOfTextures].Width,
                              &textureManager->Textures[textureManager->NumOfTextures].Height,
                              &textureManager->Textures[textureManager->NumOfTextures].Channels, DesiredChannels);

            if (textureManager->Textures[textureManager->NumOfTextures].TextureData == NULL) {
                Texture_free(&textureManager->Textures[textureManager->NumOfTextures]);
            } else {
                TextureManager_bindTextureOpenGL(&textureManager->Textures[textureManager->NumOfTextures]);
                ++textureManager->NumOfTextures;
            }
        }
    }
    free(fulldir);
    free(imgdir);
    fclose(fptr);
}

bool TextureManager_loadTexture(TextureManager *textureManager, char *cwd, char *textureName) {
    assert(textureManager != NULL);

    if (!TextureManager_isLoaded(textureManager, textureName)) {

        const int NumOfTex = textureManager->NumOfTextures;
        const int DesiredChannels = 0;
        char *imgdir = calloc(sizeof(char), (strlen(cwd) + 100));
        strcpy(imgdir, cwd);
        strcat(imgdir, RESOURCE_FILE_LOCATION);

        strcat(imgdir, textureName);
        Texture_init(&textureManager->Textures[NumOfTex]);
        strcpy(textureManager->Textures[NumOfTex].TextureName, textureName);
        textureManager->Textures[NumOfTex].TextureData =
                stbi_load(imgdir, &textureManager->Textures[NumOfTex].Width,
                          &textureManager->Textures[NumOfTex].Height,
                          &textureManager->Textures[NumOfTex].Channels, DesiredChannels);

        if (textureManager->Textures[NumOfTex].TextureData == NULL) {
            free(imgdir);
            Texture_free(&textureManager->Textures[NumOfTex]);
            return false;
        }
        TextureManager_bindTextureOpenGL(&textureManager->Textures[textureManager->NumOfTextures]);
        ++textureManager->NumOfTextures;
        free(imgdir);
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
        return &textureManager->Textures[textureManager->NumOfTextures - 1];
    }
    return &textureManager->Textures[DEFAULT_TEXTURE];
}

Texture* TextureManager_getTextureUsingID(TextureManager *textureManager, size_t index) {
    assert(textureManager != NULL);
    if (index >= textureManager->NumOfTextures) {
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
