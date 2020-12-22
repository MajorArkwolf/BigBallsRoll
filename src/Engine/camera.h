#pragma once

#include "Math/vec3.h"

typedef struct Camera {
    Vec3 Position;
    Vec3 Up;
    Vec3 Front;
    Vec3 Right;
    Vec3 WorldUp;
    float speed;
    float pitch;
    float yaw;
    float mouse_sensitivity;
} Camera;

typedef enum Direction {
    Direction_Forward,
    Direction_Backward,
    Direction_Left,
    Direction_Right
} Direction;

Camera Camera_construct();
void Camera_reset(Camera *cam);
void Camera_keyboardWalk(Camera *cam, Direction direction, float dt);
void Camera_mouseLook(Camera *cam, float x, float y, float dt);
void Camera_UpdateCameraVectors(Camera *cam);
