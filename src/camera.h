#pragma once

#include "math/vec3.h"
#include <stdbool.h>

typedef struct Camera {
    struct vec3 position;
    struct vec3 rotation;
} Camera;