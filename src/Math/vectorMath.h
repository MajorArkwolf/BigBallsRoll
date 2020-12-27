#pragma once
#include "vec3.h"
/**
 * Multiply a vector 3 by a scalar
 * @param vec3 vector to be multiplied
 * @param scalar the scalar to multiply by
 * @return the result of the operation.
 */
Vec3 VectorMath_multiplyVecByScalar(Vec3 const *vec3 , float scalar);

/**
 * Add two vectors together.
 * @param firstVec3 first vector to add
 * @param secondVec3 second vector to add
 * @return the result of the addition.
 */
Vec3 VectorMath_addVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3);

/**
 * Cross product of two vectors.
 * @param firstVec3 first vector to cross product
 * @param secondVec3 second vector to cross product
 * @return the result of the cross product
 */
Vec3 VectorMath_crossProductVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3);

/**
 * Normalise Vector
 * @param vec3 vector to normalise
 * @return the result
 */
Vec3 VectorMath_normaliseVec3(Vec3 const *vec3);
