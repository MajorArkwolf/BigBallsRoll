#include "physicsInterface.h"
#include "Engine/OpenGL.h"
#include "stdio.h"

//Global Debug Data
DebugData dd;

void PhysicsInterface_init() {
    PhysicsDebug_dataInit(&dd);
}

void PhysicsInterface_update() {

}

void PhysicsInterface_free() {
    PhysicsDebug_dataFree(&dd);
}

void PhysicsInterface_draw(PhysicsWorld *physicsWorld) {
    if(physicsWorld != NULL && PhysicsWorld_draw(physicsWorld, &dd)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);

        for (size_t i = 0; i < dd.numFaces; ++i) {
            glColor3f(dd.colour[0], dd.colour[1], dd.colour[2]);
            glVertex3f(dd.vertices->array[dd.faceIndexes->array[i]], dd.vertices->array[dd.faceIndexes->array[i] + 1], dd.vertices->array[dd.faceIndexes->array[i] + 2]);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

