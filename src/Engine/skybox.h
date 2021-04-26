#pragma  once
#include "Engine/textureManager.h"

//TODO: Temp work around for windows
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

//Skybox
Texture *skybox[6];

/**
 * Loads the 6 skybox textures into the skybox global.
 * If the skybox cant be found the default texture will be used.
 */
void Skybox_loadTexture(void);

/**
 * Draws the skybox. Must be drawn before anything else is drawn.
 */
void Skybox_draw(void);
