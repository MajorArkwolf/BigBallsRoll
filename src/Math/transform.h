#pragma once
#include "vec3.h"

typedef struct Transform {
    Vec3 Position;
    Vec3 Rotation;
    Vec3 Scale;
} Transform;

Transform Transformation_construct();

