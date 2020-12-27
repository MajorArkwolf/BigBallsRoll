#include "gameObject.h"
#include <stdlib.h>
#include "OpenGL.h"
#include "Engine/modelManager.h"
#include "main.h"

void GameObject_init(GameObject *gameObject) {
    gameObject->Name = NULL;
    gameObject->ModelID = 0;
    gameObject->Transform = Transformation_construct();
}

void GameObject_free(GameObject *gameObject) {
    free(gameObject->Name);
    GameObject_init(gameObject);
}

void GameObject_draw(GameObject *gameObject) {
    glPushMatrix();
    glRotatef(gameObject->Transform.Rotation.X, 1, 0, 0);
    glRotatef(gameObject->Transform.Rotation.Y, 0, 1, 0);
    glRotatef(gameObject->Transform.Rotation.Z, 0, 0, 1);
    glScalef(gameObject->Transform.Scale.X, gameObject->Transform.Scale.Y, gameObject->Transform.Scale.Z);
    glTranslatef(gameObject->Transform.Position.X, gameObject->Transform.Position.Y, gameObject->Transform.Position.Z);
    Model_draw(ModelManager_getModel(&modelManager, gameObject->ModelID));
    glPopMatrix();
}