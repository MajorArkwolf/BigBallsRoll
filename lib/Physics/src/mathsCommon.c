#include "include/BigBalls/mathsCommon.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <stdlib.h>

bool fTolerance(float a, float b, float tolerance){
    assert(tolerance >= 0);
    if(fabsf(a-b) < tolerance){
        return true;
    }
    else{
        return false;
    }
}

float toRad(float deg){
    return deg*(float)M_PI/180.f;
}

Matrix44 identity44() {
    Matrix44 res;
    res.elem[0][0] = 1;
    res.elem[0][1] = 0;
    res.elem[0][2] = 0;
    res.elem[0][3] = 0;
    res.elem[1][0] = 0;
    res.elem[1][1] = 1;
    res.elem[1][2] = 0;
    res.elem[1][3] = 0;
    res.elem[2][0] = 0;
    res.elem[2][1] = 0;
    res.elem[2][2] = 1;
    res.elem[2][3] = 0;
    res.elem[3][0] = 0;
    res.elem[3][1] = 0;
    res.elem[3][2] = 0;
    res.elem[3][3] = 1;
    return res;
}

bool compareMatrix44(Matrix44 a, Matrix44 b){
    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 4; ++j){
            if(a.elem[i][j] != b.elem[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool compareMatrix41(Matrix41 a, Matrix41 b){
    for(size_t i = 0; i < 4; ++i){
        if(a.elem[i] != b.elem[i]){
            return false;
        }
    }
    return true;
}

Matrix44 matrixMultiplication44_44(Matrix44 a, Matrix44 b){
    Matrix44 res;
    res = identity44();
    for(int i = 0; i < 4; ++i) { // for every row of a
        for(int j = 0; j < 4; ++j) { // for every column of b
            float sum = 0;
            for(int k = 0; k < 4; ++k){ // for every row of b
                sum += a.elem[i][k]*b.elem[k][j];
            }
            res.elem[i][j] = sum;
        }
    }
    return res;
}

Matrix41 matrixMultiplication44_41(Matrix44 a, Matrix41 b){
    Matrix41 res;
    for(int i = 0; i < 4; ++i) { // for every row of a
        float sum = 0;
        for(int j = 0; j < 4; ++j){ // for every row of b
            sum += a.elem[i][j]*b.elem[j];
        }
        res.elem[i] = sum;
    }
    return res;
}

void minMax(float val1, float val2, float* min, float* max){
    if(val1 <= val2){
        *min = val1;
        *max = val2;
    }
    else{
        *min = val2;
        *max = val1;
    }
}

void checkMin(float val, float* min){
    if(val < *min){
        *min = val;
    }
}

void testPointMinMax(const float pos, const float len, float* min, float* max){
    if(len > 0){ // positive length
        if(pos + len > *max){
            *max = pos + len;
        }
        else if(pos < *min){
            *min = pos;
        }
    }
    else{ // negative length
        if(pos > *max){
            *max = pos;
        }
        else if(pos + len < *min){
            *min = pos + len;
        }
    }
}

Matrix44 rotateAboutVec(float xVec, float yVec, float zVec, float rotDeg){
    Matrix44 res;
    res.elem[0][3] = 0;
    res.elem[1][3] = 0;
    res.elem[2][3] = 0;
    res.elem[3][3] = 1;
    float rot = rotDeg * M_PI/180;
    // rotation implementation taken from OpenGL documentation https://docs.gl/gl2/glRotate
    res.elem[0][0] = (powf(xVec, 2) * (1 - cosf(rot))) + cosf(rot);
    res.elem[0][1] = (xVec * yVec * (1 - cosf(rot))) - zVec * sinf(rot);
    res.elem[0][2] = (xVec * zVec * (1 - cosf(rot))) + yVec * sinf(rot);
    res.elem[1][0] = (yVec * xVec * (1 - cosf(rot))) + zVec * sinf(rot);
    res.elem[1][1] = (powf(yVec, 2) * (1 - cosf(rot))) + cosf(rot);
    res.elem[1][2] = (yVec * zVec * (1 - cosf(rot))) - xVec * sinf(rot);
    res.elem[2][0] = (xVec * zVec * (1 - cosf(rot))) - yVec * sinf(rot);
    res.elem[2][1] = (yVec * zVec * (1 - cosf(rot))) + xVec * sinf(rot);
    res.elem[2][2] = (powf(zVec, 2) * (1 - cosf(rot))) + cosf(rot);
    return res;
}

Matrix44 createRotMat(float xDeg, float yDeg, float zDeg){
    Matrix44 x = rotateAboutVec(1, 0, 0, xDeg);
    Matrix44 y = rotateAboutVec(0, 1, 0, yDeg);
    Matrix44 z = rotateAboutVec(0, 0, 1, zDeg);

    return matrixMultiplication44_44(z , matrixMultiplication44_44(y, x));
}

PVec3 PVec3_init() {
    PVec3 vec3;
    vec3.data[0] = 0.0f;
    vec3.data[1] = 0.0f;
    vec3.data[2] = 0.0f;
    return vec3;
}

bool isPVecsNull(const PVec3* vec1, const PVec3* vec2) {
    return vec1 == NULL || vec2 == NULL;
}

PVec3 addPVec3(const PVec3* vec1, const PVec3* vec2) {
    PVec3 result = PVec3_init();
    if (isPVecsNull(vec1, vec2)) {
        return result;
    }
    result.data[0] = vec1->data[0] + vec2->data[0];
    result.data[1] = vec1->data[1] + vec2->data[1];
    result.data[2] = vec1->data[2] + vec2->data[2];
    return result;
}

PVec3 subtractPVec3(const PVec3* vec1, const PVec3* vec2) {
    PVec3 result = PVec3_init();
    if (isPVecsNull(vec1, vec2)) {
        return result;
    }
    result.data[0] = vec1->data[0] - vec2->data[0];
    result.data[1] = vec1->data[1] - vec2->data[1];
    result.data[2] = vec1->data[2] - vec2->data[2];
    return result;
}

float dotProductPVec3(const PVec3* vec1, const PVec3* vec2) {
    float result = 0.0f;
    if (isPVecsNull(vec1, vec2)) {
        return result;
    }
    result += vec1->data[0] * vec2->data[0];
    result += vec1->data[1] * vec2->data[1];
    result += vec1->data[2] * vec2->data[2];
    return result;
}

PVec3 crossProductPVec3(const PVec3* vec1, const PVec3* vec2) {
    PVec3 result = PVec3_init();
    if (isPVecsNull(vec1, vec2)) {
        return result;
    }
    result.data[0] = vec1->data[1] * vec2->data[2] - vec1->data[2] * vec2->data[1];
    result.data[1] = vec1->data[2] * vec2->data[0] - vec1->data[0] * vec2->data[2];
    result.data[2] = vec1->data[0] * vec2->data[1] - vec1->data[1] * vec2->data[0];
    return result;
}

PVec3 PVec3MultiplyScalar(const PVec3* vec, float scalar) {
    PVec3 result = PVec3_init();
    if (vec == NULL) {
        return result;
    }
    result.data[0] = vec->data[0] * scalar;
    result.data[1] = vec->data[1] * scalar;
    result.data[2] = vec->data[2] * scalar;
    return result;
}
