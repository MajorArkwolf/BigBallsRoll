#pragma  once
#include "Engine/textureManager.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


Texture *skybox[6];

void Skybox_loadTexture(void);

void Skybox_draw(void);
