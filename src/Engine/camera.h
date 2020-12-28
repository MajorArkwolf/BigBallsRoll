#pragma once

#include "Math/vec3.h"
#include <stdbool.h>

/// Camera Structure
typedef struct Camera {
    Vec3 Position;
    Vec3 Up;
    Vec3 Front;
    Vec3 Right;
    Vec3 WorldUp;
    float Speed;
    float Pitch;
    float Yaw;
    float Mouse_sensitivity;
    bool MoveForward;
    bool MoveBackward;
    bool MoveLeft;
    bool MoveRight;
} Camera;

/**
 * Constructs a Camera object initialised to zero
 * @return a camera object allocated and initialised
 */
Camera Camera_construct();

/**
 * Resets the Camera object back to default values
 * @param cam Camera to be reset
 */
void Camera_reset(Camera *cam);

/**
 * Takes a relative mouse movement to the screen and moves the camera based of that movement
 * @param cam the camera to be moved
 * @param x the difference in x
 * @param y the difference in y
 */
void Camera_mouseLook(Camera *cam, float x, float y);

/**
 * Updates the right and up vectors for looking and moving
 * @param cam camera to be updated
 */
void Camera_updateCameraVectors(Camera *cam);

/**
 * Encapsulates the glLookAt function, sets the glLookAt based of the camera passed in
 * @param cam camera to use on the glLookAt function
 */
void Camera_lookAt(Camera *cam);

/**
 * Updates the camera based on the current inputs that are active such as move forward.
 * @param cam Camera to be updated
 * @param dt delta time since last update
 */
void Camera_update(Camera * cam, float dt);
