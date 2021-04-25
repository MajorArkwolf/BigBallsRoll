#include "physicsInterface.h"
#include "Engine/OpenGL.h"
#include "Engine/engine.h"
#include "Engine/stateManager.h"

//Global Debug Data
DebugData dd;

void PhysicsInterface_init() {
    PhysicsEngine_init(&engine.physicsEngine);
    PhysicsDebug_dataInit(&dd);
}

void PhysicsInterface_update(double deltaTime) {
    State *state = StateManager_top(&engine.sM);
    for(size_t i = 0; i < state->NumOfGameObjects; ++i) {
        GameObject *ob = &state->gameObjects[i];
        if (ob->collisionBody != NULL) {
            CollisionBody_setPos(ob->collisionBody, ob->Transform.Position.X, ob->Transform.Position.Y, ob->Transform.Position.Z);
        }
    }
    PhysicsEngine_updateWorld(StateManager_top(&engine.sM)->physicsWorld, deltaTime);
    for(size_t i = 0; i < state->NumOfGameObjects; ++i) {
        GameObject *ob = &state->gameObjects[i];
        if (ob->collisionBody != NULL && ob->collisionBody->isStatic != true) {
            ob->Transform.Position.X = ob->collisionBody->xPos;
            ob->Transform.Position.Y = ob->collisionBody->yPos;
            ob->Transform.Position.Z = ob->collisionBody->zPos;
        }
    }
}

void PhysicsInterface_free() {
    PhysicsEngine_free(&engine.physicsEngine);
    PhysicsDebug_dataFree(&dd);
}

void PhysicsInterface_draw(PhysicsWorld *physicsWorld) {
    if(physicsWorld != NULL && PhysicsWorld_draw(physicsWorld, &dd)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);

        for (size_t i = 0; i < dd.numFaces; i = i + 4) {
                glColor3f(dd.faceIndexes->array[i + 1], dd.faceIndexes->array[i + 2], dd.faceIndexes->array[i + 3]);
                glVertex3f(dd.vertices->array[dd.faceIndexes->array[i] + 0],
                           dd.vertices->array[dd.faceIndexes->array[i] + 1],
                           dd.vertices->array[dd.faceIndexes->array[i] + 2]);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

