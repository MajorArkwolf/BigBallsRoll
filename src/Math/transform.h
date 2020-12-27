#pragma once
#include "vec3.h"

typedef struct Transform {
    Vec3 Position;
    Vec3 Rotation;
    Vec3 Scale;
} Transform;

/**
 * Construct a basic transform data type. All values are zero'ed except for scale that is all ones
 * @return the transform object
 */
Transform Transformation_construct();

