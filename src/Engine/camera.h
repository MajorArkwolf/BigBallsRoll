#pragma once

#include "Math/vec3.h"
#include <stdbool.h>

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

Camera Camera_construct();
void Camera_reset(Camera *cam);
void Camera_mouseLook(Camera *cam, float x, float y);
void Camera_updateCameraVectors(Camera *cam);
void Camera_lookAt(Camera *cam);
void Camera_update(Camera * cam, float dt);
