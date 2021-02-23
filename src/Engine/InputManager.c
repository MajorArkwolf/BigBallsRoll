#include "InputManager.h"
#include "Engine/OpenGL.h"
#include <ctype.h>

InputType InputType_convertSpecialKey(int glutKey) {
    switch(glutKey) {
        default:
            return KEY_NONE;
    }
}

InputType InputType_convertRegularKey(int key) {
    switch (key) {
        case(GLFW_KEY_ESCAPE):
            //Escape key
            return KEY_ESC;
        case(GLFW_KEY_A):
            return KEY_A;
        case(GLFW_KEY_B):
            return KEY_B;
        case(GLFW_KEY_C):
            return KEY_C;
        case(GLFW_KEY_D):
            return KEY_D;
        case(GLFW_KEY_E):
            return KEY_E;
        case(GLFW_KEY_F):
            return KEY_F;
        case(GLFW_KEY_G):
            return KEY_G;
        case(GLFW_KEY_H):
            return KEY_H;
        case(GLFW_KEY_I):
            return KEY_I;
        case(GLFW_KEY_J):
            return KEY_J;
        case(GLFW_KEY_K):
            return KEY_K;
        case(GLFW_KEY_L):
            return KEY_L;
        case(GLFW_KEY_M):
            return KEY_M;
        case(GLFW_KEY_N):
            return KEY_N;
        case(GLFW_KEY_O):
            return KEY_O;
        case(GLFW_KEY_P):
            return KEY_P;
        case(GLFW_KEY_Q):
            return KEY_Q;
        case(GLFW_KEY_R):
            return KEY_R;
        case(GLFW_KEY_S):
            return KEY_S;
        case(GLFW_KEY_T):
            return KEY_T;
        case(GLFW_KEY_U):
            return KEY_U;
        case(GLFW_KEY_V):
            return KEY_V;
        case(GLFW_KEY_W):
            return KEY_W;
        case(GLFW_KEY_X):
            return KEY_X;
        case(GLFW_KEY_Y):
            return KEY_Y;
        case(GLFW_KEY_Z):
            return KEY_Z;
        case (GLFW_KEY_GRAVE_ACCENT):
            return KEY_TILDE;
        case (GLFW_KEY_1):
            return KEY_1;
        case (GLFW_KEY_2):
            return KEY_2;
        case (GLFW_KEY_3):
            return KEY_3;
        case (GLFW_KEY_4):
            return KEY_4;
        case (GLFW_KEY_5):
            return KEY_5;
        case (GLFW_KEY_6):
            return KEY_6;
        case (GLFW_KEY_7):
            return KEY_7;
        case (GLFW_KEY_8):
            return KEY_8;
        case (GLFW_KEY_9):
            return KEY_9;
        case (GLFW_KEY_0):
            return KEY_0;
        case (GLFW_KEY_MINUS):
            return KEY_DASH;
        case (GLFW_KEY_EQUAL):
            return KEY_EQUALS;
        case (GLFW_KEY_SPACE):
            return KEY_SPACEBAR;
        case(GLFW_KEY_LEFT_ALT):
            return KEY_LALT;
        case(GLFW_KEY_RIGHT_ALT):
            return KEY_RALT;
        case(GLFW_KEY_LEFT_CONTROL):
            return KEY_LCNTRL;
        case(GLFW_KEY_RIGHT_CONTROL):
            return KEY_RCNTRL;
        case(GLFW_KEY_F1):
            return KEY_F1;
        case(GLFW_KEY_F2):
            return KEY_F2;
        case(GLFW_KEY_F3):
            return KEY_F3;
        case(GLFW_KEY_F4):
            return KEY_F4;
        case(GLFW_KEY_F5):
            return KEY_F5;
        case(GLFW_KEY_F6):
            return KEY_F6;
        case(GLFW_KEY_F7):
            return KEY_F7;
        case(GLFW_KEY_F8):
            return KEY_F8;
        case(GLFW_KEY_F9):
            return KEY_F9;
        case(GLFW_KEY_F10):
            return KEY_F10;
        case(GLFW_KEY_F11):
            return KEY_F11;
        case(GLFW_KEY_F12):
            return KEY_F12;
        case(GLFW_KEY_UP):
            return KEY_UP_ARROW;
        case(GLFW_KEY_LEFT):
            return KEY_LEFT_ARROW;
        case(GLFW_KEY_RIGHT):
            return KEY_RIGHT_ARROW;
        case(GLFW_KEY_DOWN):
            return KEY_DOWN_ARROW;
        default:
            return KEY_NONE;
    }
}

InputType InputType_convertMouseButton(int glutKey) {
//    switch (glutKey) {
//        case (GLUT_LEFT_BUTTON):
//            return MOUSE_LEFT_BUTTON;
//        case (GLUT_RIGHT_BUTTON):
//            return MOUSE_RIGHT_BUTTON;
//        default:
//            return KEY_NONE;
//    }
}
