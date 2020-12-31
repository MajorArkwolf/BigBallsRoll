#pragma once

#include "stb_image.h"
#include <stdbool.h>

/// Arbitrary amount of textures, this keeps our textures on the stack so we can have faster access to them.
#define MAX_TEXTURES 1000

/// Texture Structure
typedef struct Texture {
    unsigned char *TextureData;
    char *TextureName;
    int Width;
    int Height;
    int Channels;
} Texture;

/// Texture Manager Structure
typedef struct TextureManager {
    Texture Textures[MAX_TEXTURES];
    size_t NumOfTextures;
} TextureManager;

/**
 * Frees the textureData and sets textureName to NULL
 * @param texture Texture struct to store Name and Data
 */
void Texture_free(Texture *texture);

/**
 * Initialises texture, must be allocated prior to being used
 * @param texture The texture to be initialised
 */
void Texture_init(Texture *texture);

/**
 * Initialises texture manager, must be allocated prior to being used
 * @param textureManager object to initialised
 */
void TextureManager_init(TextureManager *textureManager);

/**
 * Free objects contained inside of the texture manager
 * @param textureManager Texture manager to be freed
 */
void TextureManager_free(TextureManager *textureManager);

/**
 * Textures to be pre-loaded from a list in res/loader/textureloading.txt to be used later
 * @param textureManager Texture manager to load textures into
 * @param cwd The current working directory, must contain res folder to work
 */
void TextureManager_preLoadTextures(TextureManager *textureManager, char *cwd);

/**
 * Textures to be loaded as needed, once loaded they will be stored in memory until freed
 * Should only be used to load textures, doesnt return texture object
 * @param textureManager Texture manager to load textures into
 * @param cwd The current working directory, must contain res folder to work
 * @param textureName The name of the texture to be loaded from res/Texture
 */
bool TextureManager_loadTexture(TextureManager *textureManager, char *cwd, char *textureName);

/**
 * Finds a texture based on a name and returns its ID (index) in the texture managers textures array
 * If texture cannot be found, 0 (default texture) is returned
 * @param textureManager The texture manager to be searched
 * @param textureName The name of the texture to search for
 * @return the index of the texture in the array, if not there 0 (default texture) is returned
 */
Texture* TextureManager_getTexture(TextureManager *textureManager, char *cwd, char *textureName);

/**
 * Gets a texture object if it is found in the texture manager
 * @param textureManager The texture manager to search
 * @param index The index of the texture
 * @return The texture object if found, else DEFAULT_TEXTURE (0)
 */
Texture* TextureManager_getTextureUsingID(TextureManager *textureManager, size_t index);

/**
 * Finds a textures ID (index) in the textureManager using the texture name
 * @param textureManager The texture manager to search
 * @param textureName The name of the texture to search for
 * @return The ID (index) of the texture or DEFAULT_TEXTURE (0) if not found
 */
size_t TextureManager_findTextureID(TextureManager *textureManager, char *textureName);

/**
 * Checks if a texture is loaded in the texture manager using the textures name
 * @param textureManager The texture manager to be searched
 * @param textureName The name of the texture to search for
 * @return true if found, false otherwise
 */
bool TextureManager_isLoaded(TextureManager *textureManager, char*textureName);
