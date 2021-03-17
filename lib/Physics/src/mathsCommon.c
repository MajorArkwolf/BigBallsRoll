#include "include/BigBalls/mathsCommon.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <stdlib.h>

//TODO: Temporary
GravityNormal GravityNormal_init() {
    GravityNormal gN;
    gN.X = 0.0f;
    gN.Y = 1.0f;
    gN.Z = 0.0f;
    return gN;
}

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
    Matrix44 res = {.elem[0] = {1, 0, 0, 0},
                    .elem[1] = {0, 1, 0, 0},
                    .elem[2] = {0, 0, 1, 0},
                    .elem[3] = {0, 0, 0, 1}};
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

Matrix44 rotationTransformationMatrix(float x, float y, float z){
    float xRad = toRad(x);
    float yRad = toRad(y);
    float zRad = toRad(z);

    // tait-bryan angles, XYZ rotation matrix https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles
    // "The only difference is that Tait–Bryan angles represent rotations about three distinct axes (e.g. x-y-z, or x-y′-z″), while proper Euler angles use the same axis for both the first and third elemental rotations (e.g., z-x-z, or z-x′-z″)"
    // follows right-hand rule like glRotate(), but not 100% sure if its the same order rotations are applied (xyz sounds conventional though)
    // order should only impact impact of gimbal lock
    Matrix44 res = identity44();
    res.elem[0][0] = cosf(yRad)*cosf(zRad);
    res.elem[0][1] = -1.f*cosf(yRad)*sinf(zRad);
    res.elem[0][2] = sinf(yRad);
    res.elem[1][0] = cosf(xRad)*sinf(zRad) + cosf(zRad)*sinf(xRad)*sinf(yRad);
    res.elem[1][1] = cosf(xRad)*cosf(zRad) - sinf(xRad)*sinf(yRad)*sinf(zRad);
    res.elem[1][2] = -1.f*cosf(yRad)*sinf(xRad);
    res.elem[2][0] = sinf(xRad)*sinf(zRad) - cosf(xRad)*cosf(zRad)*sinf(yRad);
    res.elem[2][1] = cosf(zRad)*sinf(xRad) + cosf(xRad)*sinf(yRad)*sinf(zRad);
    res.elem[2][2] = cosf(xRad)*cosf(yRad);
    return res;
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
