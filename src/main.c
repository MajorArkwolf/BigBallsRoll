#include "main.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "Helper/token.h"
#include "ObjLoader/objLoader.h"

#include "Engine/camera.h"
#include "Math/transform.h"

static Model mod;
static Transform tran;
static Camera cam;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = (float) w / (float) h;

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
    //printf("X: %f, Y: %f, Z: %f\n", cam.Position.X, cam.Position.Y, cam.Position.Z);
    printf("Pitch: %f, Yaw: %f\n", cam.pitch, cam.yaw);
    //printf("update\n");
}

static void Draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    glLoadIdentity();

    gluLookAt(
            cam.Position.X, cam.Position.Y, cam.Position.Z,
            cam.Position.X + cam.Front.X, cam.Position.Y + cam.Front.Y, cam.Front.Z + cam.Front.Z,
            cam.Up.X, cam.Up.Y, cam.Up.Z);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(tran.Position.X, tran.Position.Y, tran.Position.Z);
    glScalef(tran.Scale.X, tran.Scale.Y, tran.Scale.Z);
    glRotatef(tran.Rotation.X, 1, 0, 0);
    glRotatef(tran.Rotation.Y, 0, 1, 0);
    glRotatef(tran.Rotation.Z, 0, 0, 1);

    for (size_t i = 0; i < mod.NumOfFaces; ++i) {
        glVertex3f(mod.Vertices[mod.Faces[i].One].X, mod.Vertices[mod.Faces[i].One].Y, mod.Vertices[mod.Faces[i].One].Z);
        glVertex3f(mod.Vertices[mod.Faces[i].Two].X, mod.Vertices[mod.Faces[i].Two].Y, mod.Vertices[mod.Faces[i].Two].Z);
        glVertex3f(mod.Vertices[mod.Faces[i].Three].X, mod.Vertices[mod.Faces[i].Three].Y, mod.Vertices[mod.Faces[i].Three].Z);
    }
    glPopMatrix();
//    glVertex3f(-2, -2, -5.0);
//    glVertex3f(2, 0.0, -5.0);
//    glVertex3f(0.0, 2, -5.0);
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
    //TODO: This delta time is hardcoded and is wrong.
    switch (key) {
        case GLUT_KEY_UP:
            Camera_keyboardWalk(&cam, Direction_Forward, 0.1f);
            break;
        case GLUT_KEY_DOWN:
            Camera_keyboardWalk(&cam, Direction_Backward, 0.1f);
            break;
        case GLUT_KEY_LEFT:
            Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        default:
            break;
    }
    //glutSetWindow(mainWindow);
    glutPostRedisplay();

}

void releaseKey(int key, int x, int y) {

    switch (key) {
//        case GLUT_KEY_UP :
//        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

void mouseMove(int x, int y) {
    //TODO: This delta time is hardcoded and is wrong.
    Camera_mouseLook(&cam, (float)x, (float)y, 0.1f);
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

int main(int argc, char *argv[]) {
    //Get the current working directory
    char *cwd = GetCurrentWorkingDirectory(argv[0]);
    //This is test code and can be removed later
    mod = loadModel(cwd, "bone.off");
    tran = Transformation_construct();
    tran.Scale.X = 100.f;
    tran.Scale.Y = 100.f;
    tran.Scale.Z = 100.f;
    cam = Camera_construct();


    glutInit(&argc, argv);
    //Set the window position to the centre of the screen.
    int x_offset = glutGet(GLUT_SCREEN_WIDTH) / 2 - width / 2;
    int y_offset = glutGet(GLUT_SCREEN_HEIGHT) / 2 - height / 2;

    glutInitWindowPosition(x_offset, y_offset);
    glutInitWindowSize(width, height);
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
    glutWarpPointer(x_offset, y_offset);
    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);

    glutMainLoop();

    return EXIT_SUCCESS;
}
