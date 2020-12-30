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

/**
 * Frees the textureData and sets textureName to NULL
 * @param texture Texture struct to store Name and Data
 */
void Texture_Free(Texture *texture);

/**
 * Initialises texture manager, must be allocated prior to being used
 * @param textureManager object to intialise
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
 * @param textureManager Texture manager to load textures into
 * @param cwd The current working directory, must contain res floder to work
 * @param textureName The name of the texture to be loaded from res/Texture
 */
void TextureManager_LoadTexture(TextureManager *textureManager, char *cwd, char *textureName);

/**
 * Finds a texture based on a name and returns its ID (index) in the texture managers textures array
 * If texture cannot be found, 0 (default texture) is returned
 * @param textureManager The texture manager to be searched
 * @param textureName The name of the texture to search for
 * @return the index of the texture in the array, if not there 0 (default texture) is returned
 */
size_t TextureManager_findTexture(TextureManager *textureManager, char *textureName);

/**
 * Gets a texture using an ID (index) and if found returns the texture data
 * If texture cannot be found it returns the data stored at index 0 (default texture)
 * @param textureManager The texture manager to search
 * @param Index The index of the texture being searched for
 * @return The index of the found texture, if not found; data stored at index 0 (default texture)
 */
Texture* TextureManager_getTexture(TextureManager *textureManager, size_t index);

/**
 * Checks if a texture is loaded in the texture manager using the textures name
 * @param textureManager The texture manager to be searched
 * @param textureName The name of the texture to search for
 * @return true if found, false otherwise
 */
bool TextureManager_isLoaded(TextureManager *textureManager, char*textureName);

//place somewhere else?
/**
 * Gets a file type from the name of a texture (i.e. jpg, png)
 * @param textureName The name of the texture to process
 * @return the file type extension
 */
char* getFileType(char *textureName);
