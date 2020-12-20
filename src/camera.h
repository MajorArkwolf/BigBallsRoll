#pragma once
#include "math/vec3.h"
#include <stdbool.h>

struct Camera {
    struct vec3 position;
    struct vec3 rotation;
};