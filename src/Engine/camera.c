#include "camera.h"
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "Engine/OpenGL.h"
#include "Math/vectorMath.h"
#include "Math/extraMath.h"
#include "Engine/engine.h"

#define DEFAULT_SENSITIVITY 0.1f

Camera Camera_construct() {
    Camera cam;
    Camera_reset(&cam);
    return cam;
}

void Camera_reset(Camera *cam) {
    assert(cam != NULL);
    cam->Position = Vec3_construct();
    cam->Front = Vec3_construct();
    cam->Front.Z = -1.0f;
    cam->Right = Vec3_construct();
    cam->Up = Vec3_construct();
    cam->Up.Y = 1.0f;
    cam->WorldUp = cam->Up;
    cam->Yaw = 0.0f;
    cam->Pitch = 0.0f;
    cam->Speed = 10.0f;
    cam->Mouse_sensitivity = DEFAULT_SENSITIVITY;
    cam->MoveForward = false;
    cam->MoveBackward = false;
    cam->MoveLeft = false;
    cam->MoveRight = false;
    Camera_updateCameraVectors(cam);
}

void Camera_update(Camera *cam, float dt) {
    assert(cam != NULL);
    Vec3 newVec;
    const float velocity = cam->Speed * dt * 1.0f;
    if (cam->MoveForward) {
        newVec = VectorMath_multiplyVecByScalar(&cam->Front, velocity);
        cam->Position = VectorMath_addVec3ByVec3(&cam->Position, &newVec);
    }
    if (cam->MoveBackward) {
        newVec = VectorMath_multiplyVecByScalar(&cam->Front, velocity * -1);
        cam->Position = VectorMath_addVec3ByVec3(&cam->Position, &newVec);
    }
    if (cam->MoveRight) {
        newVec = VectorMath_multiplyVecByScalar(&cam->Right, velocity);
        cam->Position = VectorMath_addVec3ByVec3(&cam->Position, &newVec);
    }
    if (cam->MoveLeft) {
        newVec = VectorMath_multiplyVecByScalar(&cam->Right, velocity * -1);
        cam->Position = VectorMath_addVec3ByVec3(&cam->Position, &newVec);
    }
    AudioEngine_listenerLocation(&cam->Position, NULL);
    AudioEngine_listenerOrientation(&cam->Front, &cam->Up);
}

void Camera_mouseLook(Camera *cam, float x, float y) {
    assert(cam != NULL);
    cam->Yaw += x * cam->Mouse_sensitivity;
    cam->Pitch += y * cam->Mouse_sensitivity;

    if (cam->Pitch > 89.0f) {
        cam->Pitch = 89.0f;
    }
    if (cam->Pitch < -89.0f) {
        cam->Pitch = -89.0f;
    }
    Camera_updateCameraVectors(cam);
}

void Camera_updateCameraVectors(Camera *cam) {
    assert(cam != NULL);
    Vec3 result;
    Vec3 front = Vec3_construct();

    float yawInRad = ExtraMath_toRadians(cam->Yaw);
    float pitchInRad = ExtraMath_toRadians(cam->Pitch);

    front.X = cosf(yawInRad) * cosf(pitchInRad);
    front.Y = sinf(pitchInRad);
    front.Z = sinf(yawInRad) * cosf(pitchInRad);
    cam->Front = VectorMath_normaliseVec3(&front);
    result = VectorMath_crossProductVec3ByVec3(&cam->Front, &cam->WorldUp);
    cam->Right = VectorMath_normaliseVec3(&result);
    result = VectorMath_crossProductVec3ByVec3(&cam->Right, &cam->Front);
    cam->Up = VectorMath_normaliseVec3(&result);
}

void Camera_lookAt(Camera *cam) {
    assert(cam != NULL);
    gluLookAt(
            cam->Position.X, cam->Position.Y, cam->Position.Z,
            cam->Position.X + cam->Front.X, cam->Position.Y + cam->Front.Y, cam->Position.Z + cam->Front.Z,
            cam->Up.X, cam->Up.Y, cam->Up.Z);
}

void Camera_lookAtObject(Camera *cam, float x, float y, float z) {
    cam->Front.X = x;
    cam->Front.Y = y;
    cam->Front.Z = z;
    cam->Front = VectorMath_normaliseVec3(&cam->Front);
}
