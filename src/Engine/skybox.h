#pragma  once

/**
 * Loads the 6 skybox textures into the skybox global.
 * If the skybox cant be found the default texture will be used.
 */
void Skybox_loadTexture(void);

/**
 * Draws the skybox. Must be drawn before anything else is drawn.
 */
void Skybox_draw(void);
