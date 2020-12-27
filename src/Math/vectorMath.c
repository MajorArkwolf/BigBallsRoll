#include "vectorMath.h"
#include <math.h>

Vec3 VectorMath_multiplyVecByScalar(Vec3 const *vec3 , float scalar) {
    Vec3 newVec;
    newVec.X = vec3->X * scalar;
    newVec.Y = vec3->Y * scalar;
    newVec.Z = vec3->Z * scalar;
    return newVec;
}

Vec3 VectorMath_addVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3) {
    Vec3 newVec;
    newVec.X = firstVec3->X + secondVec3->X;
    newVec.Y = firstVec3->Y + secondVec3->Y;
    newVec.Z = firstVec3->Z + secondVec3->Z;
    return newVec;
}

Vec3 VectorMath_crossProductVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3) {
    Vec3 newVec;
    newVec.X = firstVec3->Y * secondVec3->Z - firstVec3->Z * secondVec3->Y;
    newVec.Y = firstVec3->Z * secondVec3->X - firstVec3->X * secondVec3->Z;
    newVec.Z = firstVec3->X * secondVec3->Y - firstVec3->Y * secondVec3->X;
    return newVec;
}

Vec3 VectorMath_normaliseVec3(Vec3 const *vec3) {
    Vec3 newVec;
    float mag = sqrtf((vec3->X * vec3->X) + (vec3->Y * vec3->Y) + (vec3->Z * vec3->Z));
    newVec.X = vec3->X / mag;
    newVec.Y = vec3->Y / mag;
    newVec.Z = vec3->Z / mag;
    return newVec;
}
