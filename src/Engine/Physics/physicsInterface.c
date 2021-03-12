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

        for (size_t i = 0; i < dd.numFaces; i = i + 4) {
                glColor3f(dd.faceIndexes->array[i + 1], dd.faceIndexes->array[i + 2], dd.faceIndexes->array[i + 3]);
                glVertex3f(dd.vertices->array[dd.faceIndexes->array[i] + 0],
                           dd.vertices->array[dd.faceIndexes->array[i] + 1],
                           dd.vertices->array[dd.faceIndexes->array[i] + 2]);

            printf("%zu %zu %zu %f %f %f\n", dd.faceIndexes->array[i], dd.faceIndexes->array[i + 1], dd.faceIndexes->array[i + 2], dd.vertices->array[dd.faceIndexes->array[i] + 3], dd.vertices->array[dd.faceIndexes->array[i] + 4], dd.vertices->array[dd.faceIndexes->array[i] + 5]);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

