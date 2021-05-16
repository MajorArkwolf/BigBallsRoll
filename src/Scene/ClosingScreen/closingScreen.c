#include "closingScreen.h"
#include <Engine/engine.h>


int ClosingScreen_draw(float deltaTime) {
    glBindTexture(GL_TEXTURE_2D, closingImage->GLTextureID);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();

    return 0;
}

int ClosingScreen_keyDown(InputType inputType) {
    return 0;
}

int ClosingScreen_keyUp(InputType inputType) {
    return 0;
}

int ClosingScreen_destroy() {
    glPopAttrib(GL_LIGHTING_BIT);
    glPopAttrib(GL_ENABLE_BIT);
    return 0;
}

int ClosingScreen_update(float deltaTime) {
    return 0;
}

int ClosingScreen_mouseMovement(double x, double y) {
    return 0;
}

int ClosingScreen_mouseKeys(int button, int buttonState) {
    return 0;
}


void ClosingScreen_init(State *state) {
    glPushAttrib(GL_LIGHTING_BIT);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    Engine_cameraLock(true);
    state->update = ClosingScreen_update;
    state->draw = ClosingScreen_draw;
    state->keyDown = ClosingScreen_keyDown;
    state->keyUp = ClosingScreen_keyUp;
    state->mouseMovement = ClosingScreen_mouseMovement;
    state->mouseKeys = ClosingScreen_mouseKeys;
    state->destroy = ClosingScreen_destroy;
    state->physicsWorld = NULL;
    state->skyboxDraw = false;

    closingImage = TextureManager_getTexture(&engine.textureManager, engine.cwd, "EndScreen.png");

    Camera *cam = &StateManager_top(&engine.sM)->camera;
    cam->Position.X = -0.4f;
    engine.lockCamera = false;

    engine.guiManager.guiDraw = true;
}
