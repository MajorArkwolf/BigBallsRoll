#include "main.h"

#include "Engine/OpenGL.h"

#include <stdlib.h>
#include <stdio.h>
#include "Helper/stringPath.h"
#include "ObjLoader/objLoader.h"

#include "Engine/camera.h"
#include "Math/transform.h"
#include "Engine/stateManager.h"

static StateManager sm;

static int timeSinceStart;
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
    int oldTime = timeSinceStart;
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float) (timeSinceStart - oldTime) / 1000.0f;
    //printf("Old Time: %d, New Time: %d, DeltaTime: %f\n", oldTime, timeSinceStart, deltaTime);
    Camera_update(&cam, (float) deltaTime);
    //printf("X: %f, Y: %f, Z: %f\n", cam.Position.X, cam.Position.Y, cam.Position.Z);
    //printf("Pitch: %f, Yaw: %f\n", cam.Pitch, cam.Yaw);
    //printf("update\n");
}

static void Draw(void) {
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Camera_lookAt(&cam);
    glColor3f(255, 255, 255);

    glPushMatrix();

    glRotatef(tran.Rotation.X, 1, 0, 0);
    glRotatef(tran.Rotation.Y, 0, 1, 0);
    glRotatef(tran.Rotation.Z, 0, 0, 1);
    glScalef(tran.Scale.X, tran.Scale.Y, tran.Scale.Z);
    glTranslatef(tran.Position.X, tran.Position.Y, tran.Position.Z);

    for (size_t index = 0; index < mod.NumOfMesh; ++index) {
        if (mod.Mesh[index].Faces[0].NumFaces == 3) {
            glBegin(GL_TRIANGLES);
        } else if (mod.Mesh[index].Faces[0].NumFaces == 4) {
            glBegin(GL_QUADS);
        } else if (mod.Mesh[index].Faces[0].NumFaces > 4) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINES);
        }

        for (size_t i = 0; i < mod.Mesh[index].NumOfFaces; ++i) {
            for (size_t x = 0; x < mod.Mesh[index].Faces[i].NumFaces; ++x) {
                size_t index_val = mod.Mesh[index].Faces[i].FaceIDs[x];
                if (mod.Mesh[index].Vertices[index_val].HasTexture) {
                    //TODO: implement textures here
                }
                if (mod.Mesh[index].Faces[i].HasColour) {
                    glColor4f(mod.Mesh[index].Faces[i].Colour.RGBA[0], mod.Mesh[index].Faces[i].Colour.RGBA[1],
                              mod.Mesh[index].Faces[i].Colour.RGBA[2], mod.Mesh[index].Faces[i].Colour.RGBA[3]);
                }
                glVertex3f(mod.Mesh[index].Vertices[index_val].X, mod.Mesh[index].Vertices[index_val].Y, mod.Mesh[index].Vertices[index_val].Z);
            }
        }

        glEnd();
    }
    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    switch (key) {
        case 27:
            exit(0);
        case 'w':
        case 'W':
            cam.MoveForward = true;
            break;
        case 's':
        case 'S':
            cam.MoveBackward = true;
            break;
        case 'a':
        case 'A':
            cam.MoveLeft = true;
            break;
        case 'd':
        case 'D':
            cam.MoveRight = true;
            break;
        default:
            break;
    }
}

void processNormalKeysUp(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w':
        case 'W':
            cam.MoveForward = false;
            break;
        case 's':
        case 'S':
            cam.MoveBackward = false;
            break;
        case 'a':
        case 'A':
            cam.MoveLeft = false;
            break;
        case 'd':
        case 'D':
            cam.MoveRight = false;
            break;
        default:
            break;
    }
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP:
            cam.MoveForward = true;
            //Camera_keyboardWalk(&cam, Direction_Forward, 0.1f);
            break;
        case GLUT_KEY_DOWN:
            cam.MoveBackward = true;
            //Camera_keyboardWalk(&cam, Direction_Backward, 0.1f);
            break;
        case GLUT_KEY_LEFT:
            cam.MoveLeft = true;
            //Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            cam.MoveRight = true;
            //Camera_keyboardWalk(&cam, Direction_Right, 0.1f);
            break;
        default:
            break;
    }
    //glutSetWindow(mainWindow);
    glutPostRedisplay();

}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP:
            cam.MoveForward = false;
            //Camera_keyboardWalk(&cam, Direction_Forward, 0.1f);
            break;
        case GLUT_KEY_DOWN:
            cam.MoveBackward = false;
            //Camera_keyboardWalk(&cam, Direction_Backward, 0.1f);
            break;
        case GLUT_KEY_LEFT:
            cam.MoveLeft = false;
            //Camera_keyboardWalk(&cam, Direction_Left, 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            cam.MoveRight = false;
            //Camera_keyboardWalk(&cam, Direction_Right, 0.1f);
            break;
        default:
            break;
    }
}

void mouseMove(int x, int y) {
    float lastX = (float) x - glutGet(GLUT_WINDOW_WIDTH) / 2;
    float lastY = ((float) y - glutGet(GLUT_WINDOW_HEIGHT) / 2) * -1;
    Camera_mouseLook(&cam, lastX, lastY);
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
    //This is test code and can be removed later
    mod = loadModel(cwd, "Off/colourcube.off");
    Model_modelToOFF(&mod);
    tran = Transformation_construct();
    tran.Scale.X = 1.f;
    tran.Scale.Y = 1.f;
    tran.Scale.Z = 1.f;
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

    return EXIT_SUCCESS;
}
