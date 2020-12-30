#pragma once

#include "stb_image.h"
#include <stdbool.h>

/// Arbitrary amount of textures, this keeps our textures on the stack so we can have faster access to them.
#define MAX_TEXTURES 1000

/// Texture Structure
typedef struct Texture {
    unsigned char *textureData;
    char *textureName;
} Texture;

/// Texture Manager Structure
typedef struct TextureManager {
    Texture Textures[MAX_TEXTURES];
    size_t NumOfTextures;
} TextureManager;

void Texture_Free(Texture *texture);

void TextureManager_init(TextureManager *textureManager);

void TextureManager_free(TextureManager *textureManager);

void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd);

void TextureManager_LoadTexture(TextureManager *textureManager, char *cwd, char *textureName);

size_t TextureManager_findTexture(TextureManager *textureManager, char *textureName);

Texture* TextureManager_getTexture(TextureManager *textureManager, size_t index);

bool TextureManager_isLoaded(TextureManager *textureManager, char*textureName);

//place somewhere else?
char* getFileType(char *textureName);
