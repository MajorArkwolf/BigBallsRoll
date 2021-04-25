#include "skybox.h"
#include "OpenGL.h"
#include "Engine/engine.h"

void Skybox_loadTexture(void) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    skybox[0] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_front.jpg");
    skybox[1] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_left.jpg");
    skybox[2] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_back.jpg");
    skybox[3] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_right.jpg");
    skybox[4] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_top.jpg");
    skybox[5] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_bottom.jpg");
}

void Skybox_draw(void) {
    glPushMatrix();

    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, skybox[0]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, skybox[1]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, skybox[2]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );

    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, skybox[3]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, skybox[4]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();

    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, skybox[5]->GLTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();

    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
}
