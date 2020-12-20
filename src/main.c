#ifdef __APPLE__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  (float)w / (float)h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 10000.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

static void Update(int vlaue) {
    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);
    //printf("update\n");
}

static void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex3f(-2,-2,-5.0);
    glVertex3f(2,0.0,-5.0);
    glVertex3f(0.0,2,-5.0);
    glEnd();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

    if (key == 27) {
        //glutDestroyWindow(mainWindow);
        exit(0);
    }
}

void pressKey(int key, int xx, int yy) {

//    switch (key) {
//        case GLUT_KEY_UP : deltaMove = 0.5f; break;
//        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
//    }
//    glutSetWindow(mainWindow);
//    glutPostRedisplay();

}

void releaseKey(int key, int x, int y) {

    switch (key) {
//        case GLUT_KEY_UP :
//        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

void mouseMove(int x, int y) {

    // this will only be true when the left button is down
//    if (xOrigin >= 0) {
//
//        // update deltaAngle
//        deltaAngle = (x - xOrigin) * 0.001f;
//
//        // update camera's direction
//        lx = sin(angle + deltaAngle);
//        lz = -cos(angle + deltaAngle);
//
//        glutSetWindow(mainWindow);
//        glutPostRedisplay();
//    }
}

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
//
//        // when the button is released
//        if (state == GLUT_UP) {
//            angle += deltaAngle;
//            deltaAngle = 0.0f;
//            xOrigin = -1;
//        }
//        else  {// state = GLUT_DOWN
//            xOrigin = x;
//        }
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    bool is_running = TRUE;
    //Set the dimensions of the window

    //Set the window position to the centre of the screen.
    int x_offset = glutGet(GLUT_SCREEN_WIDTH) / 2 - width / 2;
    int y_offset = glutGet(GLUT_SCREEN_HEIGHT) / 2 - height / 2;

    glutInitWindowPosition (x_offset,y_offset);
    glutInitWindowSize ( width, height );
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Plachinko");
    if (!glutExtensionSupported("GL_EXT_abgr")) {
        printf("Couldn't find abgr extension.\n");
        exit(EXIT_FAILURE);
    }

    // Render Que
    glutDisplayFunc(Draw);
    glutReshapeFunc(changeSize);
    glutIdleFunc(Draw);

    // register callbacks
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);

    glutMainLoop();

    return EXIT_FAILURE;
}