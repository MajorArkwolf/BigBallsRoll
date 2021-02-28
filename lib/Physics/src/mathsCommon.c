#include "include/BigBalls/mathsCommon.h"
#include <math.h>
#include <stdbool.h>

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

void rotationTransformationMatrix(float x, float y, float z, float res[3][3]){
    assert(res != NULL);
    float xRad, yRad, zRad = 0;
    xRad = toRad(x);
    yRad = toRad(y);
    zRad = toRad(z);

    // tait-bryan angles, XYZ rotation matrix https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles
    // "The only difference is that Tait–Bryan angles represent rotations about three distinct axes (e.g. x-y-z, or x-y′-z″), while proper Euler angles use the same axis for both the first and third elemental rotations (e.g., z-x-z, or z-x′-z″)"
    // follows right-hand rule like glRotate(), but not 100% sure if its the same order rotations are applied (xyz sounds conventional though)
    res[0][0] = cosf(yRad)*cosf(zRad);
    res[0][1] = -1.f*cosf(yRad)*sinf(zRad);
    res[0][2] = sinf(yRad);
    res[1][0] = cosf(xRad)*sinf(zRad) + cosf(zRad)*sinf(xRad)*sinf(yRad);
    res[1][1] = cosf(xRad)*cosf(zRad) - sinf(xRad)*sinf(yRad)*sinf(zRad);
    res[1][2] = -1.f*cosf(yRad)*sinf(xRad);
    res[2][0] = sinf(xRad)*sinf(zRad) - cosf(xRad)*cosf(zRad)*sinf(yRad);
    res[2][1] = cosf(zRad)*sinf(xRad) + cosf(xRad)*sinf(yRad)*sinf(zRad);
    res[2][2] = cosf(xRad)*cosf(yRad);
}

void matrixMultiplication(int a_numRow,
                          int a_numCol,
                          int b_numRow,
                          int b_numCol,
                          float a[a_numRow][a_numCol],
                          float b[b_numRow][b_numCol],
                          float res[a_numRow][b_numCol]){
    assert(a != NULL && b != NULL && a_numRow > 0 && a_numCol > 0 && b_numRow > 0 && b_numCol > 0 && a_numCol == b_numRow);

    for(int i = 0; i < a_numRow; ++i)
    {
        for(int j = 0; j < b_numCol; ++j)
        {
            float sum = 0;
            for(int k = 0; k < b_numRow; ++k){
                sum += a[i][k]*b[k][j];
            }
            res[i][j] = sum;
        }
    }
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
