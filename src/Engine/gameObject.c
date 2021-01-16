#include "gameObject.h"
#include <stdlib.h>
#include "OpenGL.h"
#include "Engine/modelManager.h"
#include "Engine/engine.h"


void GameObject_init(GameObject *gameObject) {
    gameObject->Name = NULL;
    gameObject->ModelID = 0;
    gameObject->SoundID = 0;
    gameObject->Transform = Transformation_construct();
    gameObject->StaticObject = false;
}

void GameObject_free(GameObject *gameObject) {
    free(gameObject->Name);
    GameObject_init(gameObject);
}

void GameObject_draw(GameObject *gameObject) {
    glPushMatrix();
    glScalef(gameObject->Transform.Scale.X, gameObject->Transform.Scale.Y, gameObject->Transform.Scale.Z);
    glTranslatef(gameObject->Transform.Position.X, gameObject->Transform.Position.Y, gameObject->Transform.Position.Z);
    glRotatef(gameObject->Transform.Rotation.Z, 0, 0, 1);
    glRotatef(gameObject->Transform.Rotation.Y, 0, 1, 0);
    glRotatef(gameObject->Transform.Rotation.X, 1, 0, 0);
    Model_draw(ModelManager_getModel(&engine.modelManager, gameObject->ModelID));
    glPopMatrix();
}

void GameObject_update(GameObject *gameObject) {
    if (!gameObject->StaticObject && gameObject->SoundID > 0) {
        AudioEngine_updateSource(gameObject->SoundID, &gameObject->Transform.Position, NULL);
    }
}

void GameObject_registerSoundSource(GameObject *gameObject) {
    gameObject->SoundID = AudioEngine_newSource(&engine.audioEngine, &gameObject->Transform.Position, NULL);
}