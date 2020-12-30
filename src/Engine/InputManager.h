#pragma once

typedef enum InputType {
    // Alphabet Keys
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    //Numbers
    KEY_TILDE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_DASH,
    KEY_EQUALS,

    //Special Keys
    KEY_TAB,
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCNTRL,
    KEY_RCNTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_SPACEBAR,
    KEY_UP_ARROW,
    KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,
    KEY_RIGHT_ARROW,
    KEY_ENTER,
    KEY_BACKSPACE,
    KEY_ESC,

    //F Keys
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    //Mouse Buttons
    MOUSE_LEFT_BUTTON,
    MOUSE_RIGHT_BUTTON,

    //None represented key
    KEY_NONE

} InputType;

/**
 * Converts a glut key to our engine enum representation
 * @param glutKey special keys are represented as ints
 * @return enum of the representation of our key
 */
InputType InputType_convertSpecialKey(int glutKey);

/**
 * Converts a glut key to our engine enum representation
 * @param glutKey normal keys are represented as chars
 * @return enum of the representation of our key
 */
InputType InputType_convertRegularKey(char glutKey);

/**
 * Converts a glut mouse key into our engine enum representation
 * @param glutKey integer representation by glut
 * @return enum of the representation of our key
 */
InputType InputType_convertMouseButton(int glutKey);
