#pragma once
#include "vec3.h"

Vec3 VectorMath_MultiplyVecByScalar(Vec3 const *vec3 , float scalar);

Vec3 VectorMath_AddVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3);

Vec3 VectorMath_CrossProductVec3ByVec3(Vec3 const *firstVec3, Vec3 const *secondVec3);

Vec3 VectorMath_NormaliseVec3(Vec3 const *vec3);