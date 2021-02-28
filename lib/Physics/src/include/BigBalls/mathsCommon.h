#pragma once
// TODO: move to external math library

//TODO: Temp until vec3 is apart of external library
typedef struct GravityNormal {
    float X;
    float Y;
    float Z;
} GravityNormal;

//TODO: Temp until vec3 is apart of external library
GravityNormal GravityNormal_init();

bool fTolerance(float a, float b, float tolerance);

float toRad(float deg);

/**
 * Creates a rotation transformation matrix
 * @param x the number of degrees to rotate about the x axis (right-hand rule)
 * @param y the number of degrees to rotate about the y axis (right-hand rule)
 * @param z the number of degrees to rotate about the z axis (right-hand rule)
 * @param res the resulting transformation matrix
 */
void rotationTransformationMatrix(float x, float y, float z, float res[3][3]);

/**
 * Performs matrix multiplication of two compatible matrices. Throws assertion if matrices are incompatible.
 * @param a_numRow the number of rows in the first matrix
 * @param a_numCol the number of columns in the first matrix
 * @param b_numRow the number of rows in the second matrix
 * @param b_numCol the number of columns in the second matrix
 * @param a the first matrix
 * @param b the second matrix
 * @param res the resulting matrix
 */
void matrixMultiplication(int a_numRow,
                          int a_numCol,
                          int b_numRow,
                          int b_numCol,
                          float a[a_numRow][a_numCol],
                          float b[b_numRow][b_numCol],
                          float res[a_numRow][b_numCol]);

void minMax(float val1, float val2, float* min, float* max);

void testPointMinMax(float pos, float len, float* min, float* max);
