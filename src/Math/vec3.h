#pragma once
typedef struct Vec3 {
    float X;
    float Y;
    float Z;
} Vec3;

/**
 * Construct a zero'ed out vector
 * @return the result
 */
Vec3 Vec3_construct();
