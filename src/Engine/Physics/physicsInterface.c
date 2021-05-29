#include "physicsInterface.h"
#include "Engine/OpenGL.h"
#include "Engine/engine.h"

//Global Debug Data
DebugData dd;
//Global debug sphere Model
Model *debugSphere = NULL;

void PhysicsInterface_init() {
    PhysicsEngine_init(&engine.physicsEngine);
    PhysicsDebug_dataInit(&dd);
    debugSphere = ModelManager_getModel(&engine.modelManager, ModelManager_findModel(&engine.modelManager, "Off/debugSphere.off"));
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
        glPushAttrib(GL_ENABLE_BIT|GL_LINE_BIT|GL_POLYGON_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(3);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // Draw AABB
        for(size_t i = 0; i < dd.numFaces; i += 6) {
            glColor3ub(dd.faceIndexes->array[i + 0], dd.faceIndexes->array[i + 1], dd.faceIndexes->array[i + 2]);
            glBegin(GL_TRIANGLES);
            for(size_t j = i + 3; j < i + 6; ++j) {
                glVertex3f(dd.vertices->array[dd.faceIndexes->array[j] + 0],
                           dd.vertices->array[dd.faceIndexes->array[j] + 1],
                           dd.vertices->array[dd.faceIndexes->array[j] + 2]);
            }
            glEnd();
        }

        // Draw sphere colliders
        if (debugSphere != NULL) {
            for (size_t i = 0; i < dd.sphereData->size; i += 4) {
                glPushMatrix();
                glTranslatef(dd.sphereData->array[i + 1], dd.sphereData->array[i + 2], dd.sphereData->array[i + 3]);
                glScalef(dd.sphereData->array[i], dd.sphereData->array[i], dd.sphereData->array[i]);
                Model_draw(debugSphere);
                glPopMatrix();
            }
        }

        glPopAttrib();
    }
}

void PhysicsInterface_addForce(CollisionBody *cb, float xForce, float yForce, float zForce) {
    CollisionBody_addForce(cb, xForce, yForce, zForce);
}
