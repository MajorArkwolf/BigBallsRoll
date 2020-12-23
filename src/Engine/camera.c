#include "camera.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Math/vectorMath.h"

#define DEFAULT_SENSITIVITY 1.0f

Camera Camera_construct() {
    Camera cam;
    Camera_reset(&cam);
    return cam;
}

void Camera_reset(Camera *cam) {
    assert(cam != NULL);
    cam->Position = Vec3_Construct();
    cam->Front = Vec3_Construct();
    cam->Front.Z = -1.0f;
    cam->Right = Vec3_Construct();
    cam->Up = Vec3_Construct();
    cam->Up.Y = 1.0f;
    cam->WorldUp = cam->Up;
    cam->yaw = 0.0f;
    cam->pitch = 0.0f;
    cam->speed = 1.0f;
    cam->mouse_sensitivity = DEFAULT_SENSITIVITY;
    Camera_UpdateCameraVectors(cam);
}

void Camera_keyboardWalk(Camera *cam, Direction direction, float dt) {
    assert(cam != NULL);
    Vec3 newVec;
    const float velocity = cam->speed * dt * 100.0f;
    switch (direction) {
        case Direction_Forward:
            newVec = VectorMath_MultiplyVecByScalar(&cam->Front, velocity);
            cam->Position = VectorMath_AddVec3ByVec3(&cam->Position, &newVec);
            break;
        case Direction_Backward:
            newVec = VectorMath_MultiplyVecByScalar(&cam->Front, velocity * -1);
            cam->Position = VectorMath_AddVec3ByVec3(&cam->Position, &newVec);
            break;
        case Direction_Right:
            newVec = VectorMath_MultiplyVecByScalar(&cam->Right, velocity);
            cam->Position = VectorMath_AddVec3ByVec3(&cam->Position, &newVec);
            break;
        case Direction_Left:
            newVec = VectorMath_MultiplyVecByScalar(&cam->Right, velocity * -1);
            cam->Position = VectorMath_AddVec3ByVec3(&cam->Position, &newVec);
            break;
        default:
            break;
    }

}

void Camera_mouseLook(Camera *cam, float x, float y, float dt) {
    assert(cam != NULL);
    x *= cam->mouse_sensitivity;
    y *= cam->mouse_sensitivity;
    cam->yaw += x;
    cam->pitch +=y;

    if (cam->pitch > 89.0f) {
        cam->pitch = 89.0f;
    }
    if (cam->pitch < -89.0f) {
        cam->pitch = -89.0f;
    }
    Camera_UpdateCameraVectors(cam);
}

void Camera_UpdateCameraVectors(Camera *cam) {
    assert(cam != NULL);
    Vec3 result;
    Vec3 front = Vec3_Construct();
    front.X = cosf(cam->yaw) * cosf(cam->pitch);
    front.Y = sinf(cam->pitch);
    front.Z = sinf(cam->pitch) * cosf(cam->pitch);
    cam->Front = VectorMath_NormaliseVec3(&front);
    result = VectorMath_CrossProductVec3ByVec3(&cam->Front, &cam->WorldUp);
    cam->Right = VectorMath_NormaliseVec3(&result);
    result = VectorMath_CrossProductVec3ByVec3(&cam->Right, &cam->Front);
    cam->Up = VectorMath_NormaliseVec3(&result);
}
