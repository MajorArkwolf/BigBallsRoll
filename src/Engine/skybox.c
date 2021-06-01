#include "skybox.h"
#include "OpenGL.h"
#include "Engine/engine.h"

//Skybox
Texture *skybox[6];

void Skybox_loadTexture(void) {
    skybox[0] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_front.jpg");
    skybox[1] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_left.jpg");
    skybox[2] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_back.jpg");
    skybox[3] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_right.jpg");
    skybox[4] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_top.jpg");
    skybox[5] = TextureManager_getTexture(&engine.textureManager, engine.cwd, "skybox_bottom.jpg");
}

float cube[8][3] = {
    {-0.5f, -0.5f, -0.5f},  // 0
    {-0.5f, -0.5f, 0.5f},   // 1
    {-0.5f, 0.5f, -0.5f},   // 2
    {-0.5f, 0.5f, 0.5f},    // 3
    {0.5f, 0.5f, 0.5f},     // 4
    {0.5f, 0.5f, -0.5f},    // 5
    {0.5f, -0.5f, 0.5f},    // 6
    {0.5f, -0.5f, -0.5f}    // 7
};

float texCoords[4][2] = {
    {0,0},
    {0,1},
    {1,0},
    {1,1}
};

int texIndex[6][4] = {
    {0, 2, 3, 1},       // Front
    {0, 2, 3, 1},       // Left
    {0, 2, 3, 1},       // Back
    {0, 2, 3, 1},       // Right
    {2, 3, 1, 0},       // Top
    {3, 2, 0, 1}        // Bottom
};

int cubeIndex[6][4] = {
    {7, 0, 2, 5},       // Front
    {6, 7, 5, 4},       // Left
    {1, 6, 4, 3},       // Back
    {0, 1, 3, 2},       // Right
    {2, 3, 4, 5},       // Top
    {0, 1, 6, 7}        // Bottom
};

void Skybox_draw(void) {
    if(StateManager_top(&engine.sM)->skyboxDraw) {
        glPushMatrix();
        Camera *cam = &StateManager_top(&engine.sM)->camera;
        // Reset and transform the matrix.
        glLoadIdentity();
        gluLookAt(
            0, 0, 0,
            cam->Front.X, cam->Front.Y, cam->Front.Z,
            0, 1, 0);

        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);

        glColor4f(1, 1, 1, 1);

        for (size_t i = 0; i < 6; ++i) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, skybox[i]->GLTextureID);

            glBegin(GL_QUADS);
            for (size_t j = 0; j < 4; ++j) {
                glTexCoord2f(texCoords[texIndex[i][j]][0], texCoords[texIndex[i][j]][1]);
                glVertex3f(cube[cubeIndex[i][j]][0], cube[cubeIndex[i][j]][1], cube[cubeIndex[i][j]][2]);
            }
            glEnd();
        }

        // Restore enable bits and matrix
        glPopAttrib();
        glPopMatrix();
    }
}
