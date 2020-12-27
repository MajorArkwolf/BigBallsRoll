#include "main.h"

#include "Engine/OpenGL.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Helper/stringPath.h"
#include "ObjLoader/objLoader.h"

#include "Engine/camera.h"
#include "Math/transform.h"

#include "Engine/gameObject.h"

#include "Scene/MainMenu/mainMenu.h"

const float FRAMERATE = 1/60.0f;                     // ~60 FPS.
const float FRAMERATE_MILLIS = 1/60.0f * 1000;       // Millisecond version of framerate.
const float PHYSICS_MILLIS = 200;
int width = 1920;
int height = 1080;

int timeSinceStart;
ModelManager modelManager;
StateManager sM;

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
    Camera *cam = &StateManager_top(&sM)->camera;
    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);
    int oldTime = timeSinceStart;
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float) (timeSinceStart - oldTime) / 1000.0f;
    //printf("Old Time: %d, New Time: %d, DeltaTime: %f\n", oldTime, timeSinceStart, deltaTime);
    StateManager_update(&sM, deltaTime);
    Camera_update(cam, (float) deltaTime);
    //printf("X: %f, Y: %f, Z: %f\n", cam.Position.X, cam.Position.Y, cam.Position.Z);
    //printf("Pitch: %f, Yaw: %f\n", cam.Pitch, cam.Yaw);
    //printf("update\n");
}

static void Draw(void) {
    int oldTime = timeSinceStart;
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float) (timeSinceStart - oldTime) / 1000.0f;

    Camera *cam = &StateManager_top(&sM)->camera;
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Camera_lookAt(cam);
    glColor3f(255, 255, 255);

    glPushMatrix();
    StateManager_draw(&sM, deltaTime);
    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    Camera *cam = &StateManager_top(&sM)->camera;
    switch (key) {
        case 27:
            exit(0);
        case 'w':
        case 'W':
            cam->MoveForward = true;
            break;
        case 's':
        case 'S':
            cam->MoveBackward = true;
            break;
        case 'a':
        case 'A':
            cam->MoveLeft = true;
            break;
        case 'd':
        case 'D':
            cam->MoveRight = true;
            break;
        default:
            break;
    }
}

void processNormalKeysUp(unsigned char key, int xx, int yy) {
    Camera *cam = &StateManager_top(&sM)->camera;
    switch (key) {
        case 'w':
        case 'W':
            cam->MoveForward = false;
            break;
        case 's':
        case 'S':
            cam->MoveBackward = false;
            break;
        case 'a':
        case 'A':
            cam->MoveLeft = false;
            break;
        case 'd':
        case 'D':
            cam->MoveRight = false;
            break;
        default:
            break;
    }
}

void pressKey(int key, int xx, int yy) {
    Camera *cam = &StateManager_top(&sM)->camera;
    switch (key) {
        case GLUT_KEY_UP:
            cam->MoveForward = true;
            //Camera_keyboardWalk(&cam, Direction_Forward, 0.1f);
            break;
        case GLUT_KEY_DOWN:
            cam->MoveBackward = true;
            //Camera_keyboardWalk(&cam, Direction_Backward, 0.1f);
            break;
        case GLUT_KEY_LEFT:
            cam->MoveLeft = true;
            //Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            cam->MoveRight = true;
            //Camera_keyboardWalk(&cam, Direction_Right, 0.1f);
            break;
        default:
            break;
    }
    //glutSetWindow(mainWindow);
    glutPostRedisplay();

}

void releaseKey(int key, int x, int y) {
    Camera *cam = &StateManager_top(&sM)->camera;
    switch (key) {
        case GLUT_KEY_UP:
            cam->MoveForward = false;
            //Camera_keyboardWalk(&cam, Direction_Forward, 0.1f);
            break;
        case GLUT_KEY_DOWN:
            cam->MoveBackward = false;
            //Camera_keyboardWalk(&cam, Direction_Backward, 0.1f);
            break;
        case GLUT_KEY_LEFT:
            cam->MoveLeft = false;
            //Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            cam->MoveRight = false;
            //Camera_keyboardWalk(&cam, Direction_Right, 0.1f);
            break;
        default:
            break;
    }
}

void mouseMove(int x, int y) {
    Camera *cam = &StateManager_top(&sM)->camera;
    float lastX = (float) x - glutGet(GLUT_WINDOW_WIDTH) / 2;
    float lastY = ((float) y - glutGet(GLUT_WINDOW_HEIGHT) / 2) * -1;
    Camera_mouseLook(cam, lastX, lastY);
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
    char *cwd = getCurrentWorkingDirectory(argv[0]);

    ModelManager_init(&modelManager);
    ModelManager_loadModels(&modelManager, cwd);

    StateManager_init(&sM);
    State state;
    State_init(&state);
    MainMenu_init(&state);
    StateManager_push(&sM, &state);
    assert(sM.stack[sM.top] != NULL);

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
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processNormalKeysUp);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();

    ModelManager_free(&modelManager);
    return EXIT_SUCCESS;
}
