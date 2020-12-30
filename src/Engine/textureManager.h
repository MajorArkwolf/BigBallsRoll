#pragma once

#include "stb_image.h"

/// Arbitrary amount of textures, this keeps our textures on the stack so we can have faster access to them.
#define MAX_TEXTURES 1000

/// Texture Structure
typedef struct Texture {
    const unsigned char *textureData;
    const char *textureName;
} Texture;

/// Texture Manager Structure
typedef struct TextureManager {
    Texture Textures[MAX_TEXTURES];
    size_t NumOfTextures;
} TextureManager;

void TextureManager_init(TextureManager *textureManager);

void TextureManager_free(TextureManager *textureManager);

void TextureManager_loadTextures(TextureManager *textureManager, char *cwd);

size_t TextureManager_findTexture(TextureManager *textureManager, char *textureName);

Texture* TextureManager_getTexture(TextureManager *textureManager, size_t index);
