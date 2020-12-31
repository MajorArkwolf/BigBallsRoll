#include "InputManager.h"
#include "Engine/OpenGL.h"
#include <ctype.h>

InputType InputType_convertSpecialKey(int glutKey) {
    switch(glutKey) {
        case(GLUT_KEY_ALT_L):
            return KEY_LALT;
        case(GLUT_KEY_ALT_R):
            return KEY_RALT;
        case(GLUT_KEY_CTRL_L):
            return KEY_LCNTRL;
        case(GLUT_KEY_CTRL_R):
            return KEY_RCNTRL;
        case(GLUT_KEY_F1):
            return KEY_F1;
        case(GLUT_KEY_F2):
            return KEY_F2;
        case(GLUT_KEY_F3):
            return KEY_F3;
        case(GLUT_KEY_F4):
            return KEY_F4;
        case(GLUT_KEY_F5):
            return KEY_F5;
        case(GLUT_KEY_F6):
            return KEY_F6;
        case(GLUT_KEY_F7):
            return KEY_F7;
        case(GLUT_KEY_F8):
            return KEY_F8;
        case(GLUT_KEY_F9):
            return KEY_F9;
        case(GLUT_KEY_F10):
            return KEY_F10;
        case(GLUT_KEY_F11):
            return KEY_F11;
        case(GLUT_KEY_F12):
            return KEY_F12;
        case(GLUT_KEY_UP):
            return KEY_UP_ARROW;
        case(GLUT_KEY_LEFT):
            return KEY_LEFT_ARROW;
        case(GLUT_KEY_RIGHT):
            return KEY_RIGHT_ARROW;
        case(GLUT_KEY_DOWN):
            return KEY_DOWN_ARROW;
        default:
            return KEY_NONE;
    }
}

InputType InputType_convertRegularKey(char glutKey) {
    if (glutKey >= 'A' && glutKey <= 'z') {
        glutKey = (char) tolower(glutKey);
    }
    switch (glutKey) {
        case(27):
            //Escape key
            return KEY_ESC;
        case('a'):
            return KEY_A;
        case('b'):
            return KEY_B;
        case('c'):
            return KEY_C;
        case('d'):
            return KEY_D;
        case('e'):
            return KEY_E;
        case('f'):
            return KEY_F;
        case('g'):
            return KEY_G;
        case('h'):
            return KEY_H;
        case('i'):
            return KEY_I;
        case('j'):
            return KEY_J;
        case('k'):
            return KEY_K;
        case('l'):
            return KEY_L;
        case('m'):
            return KEY_M;
        case('n'):
            return KEY_N;
        case('o'):
            return KEY_O;
        case('p'):
            return KEY_P;
        case('q'):
            return KEY_Q;
        case('r'):
            return KEY_R;
        case('s'):
            return KEY_S;
        case('t'):
            return KEY_T;
        case('u'):
            return KEY_U;
        case('v'):
            return KEY_V;
        case('w'):
            return KEY_W;
        case('x'):
            return KEY_X;
        case('y'):
            return KEY_Y;
        case('z'):
            return KEY_Z;
        case ('`'):
            return KEY_TILDE;
        case ('1'):
            return KEY_1;
        case ('2'):
            return KEY_2;
        case ('3'):
            return KEY_3;
        case ('4'):
            return KEY_4;
        case ('5'):
            return KEY_5;
        case ('6'):
            return KEY_6;
        case ('7'):
            return KEY_7;
        case ('8'):
            return KEY_8;
        case ('9'):
            return KEY_9;
        case ('0'):
            return KEY_0;
        case ('-'):
            return KEY_DASH;
        case ('='):
            return KEY_EQUALS;
        case (' '):
            return KEY_SPACEBAR;
        default:
            return KEY_NONE;
    }
}

InputType InputType_convertMouseButton(int glutKey) {
    switch (glutKey) {
        case (GLUT_LEFT_BUTTON):
            return MOUSE_LEFT_BUTTON;
        case (GLUT_RIGHT_BUTTON):
            return MOUSE_RIGHT_BUTTON;
        default:
            return KEY_NONE;
    }
}
