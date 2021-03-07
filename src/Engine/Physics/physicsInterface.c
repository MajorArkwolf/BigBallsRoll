#include "physicsInterface.h"
#include "Engine/OpenGL.h"
#include <stdbool.h>
#include "../lib/Physics/src/include/BigBalls/physicsDebug.h"
#include "../lib/Physics/src/include/BigBalls/physicsWorld.h"
#include "stdio.h"

//Global Debug Data
DebugData dd;

void PhysicsInterface_init() {
    PhysicsDebug_dataInit(&dd);

}

void PhysicsInterface_update() {

}

void txt() {
    FILE *x;
    x = fopen("output.txt", "w");
    fprintf(x,"%s\n", "Vertices");
    for(size_t i = 0; i < dd.numVertices; ++i) {
        if (i % 3 == 0) {
            fprintf(x,"\n%s%zu\n", "//", i/3);
        }
        fprintf(x, "%f\n", dd.vertices->array[i]);
    }
    fprintf(x,"%s\n", "Indices");
    for(size_t i = 0; i < dd.numVertices; ++i) {
        if (i % 3 == 0) {
            fprintf(x,"\n%s%zu\n", "//", i/3);
        }
        fprintf(x, "%zu\n", dd.faceIndexes->array[i]);
    }
    fprintf(x,"%s\n", "How im trying to put them together");
    for (size_t i = 0; i < dd.numFaces; ++i) {
        if (i % 3 == 0) {
            fprintf(x,"\n%s%zu\n", "//", i/3);
        }
        fprintf(x, "%f % f %f\n", dd.vertices->array[dd.faceIndexes->array[i]], dd.vertices->array[dd.faceIndexes->array[i] + 1], dd.vertices->array[dd.faceIndexes->array[i] + 2]);
    }
    fclose(x);
}

void PhysicsInterface_draw(PhysicsWorld *physicsWorld) {
//    if (render == true && debuginfo != NULL) {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        glBegin(GL_TRIANGLES);
//        for (size_t i = 0; i < totalSize; i += 3) {
//            glColor3f(color.x, color.y, color.z);
//            glVertex3f(vertix[face.x], vertix[face.y], vertix[face.z])
//        }
//        glEnd();
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    }

    if(PhysicsWorld_draw(physicsWorld, &dd)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);

        /*for (size_t i = 0; i < dd.numFaces; ++i) {
            glColor3f(dd.colour[0], dd.colour[1], dd.colour[2]);
            glVertex3f(dd.vertices->array[dd.faceIndexes->array[i]], dd.vertices->array[dd.faceIndexes->array[i] + 1], dd.vertices->array[dd.faceIndexes->array[i] + 2]);
        }*/

        glColor3f(255, 255, 0);
        glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
        glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
        glVertex3f( 1.0f,-1.0f, 0.0f);
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        txt();
    }
}

