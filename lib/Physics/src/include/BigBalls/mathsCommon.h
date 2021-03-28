#pragma once
#include <stdbool.h>

// TODO: move to external math library

//TODO: Temp until vec3 is apart of external library
typedef struct tempVec3 {
    float X;
    float Y;
    float Z;
} tempVec3;

/**
 * Initialise a vec3 object.
 * @param vec the vector to be initialised
 */
void tempVec3_init(tempVec3 *vec3);

typedef struct Matrix44 { // 4 by 4 matrix
    float elem[4][4];
} Matrix44;

typedef struct Matrix41{ // 4 by 1 matrix
    float elem[4];
} Matrix41;

/**
 * Determines if two floats are "equal" given a level of tolerance
 * @param a the first float
 * @param b the second float
 * @param tolerance the tolerance allowed between the two floats for them to be considered equal
 * @return bool returns true if floats are within tolerance, false otherwise
 */
bool fTolerance(float a, float b, float tolerance);

/**
 * Converts an angle in degrees to radians
 * @param deg the angle in degrees
 * @return float the angle in radians
 */
float toRad(float deg);

/**
 * Performs matrix multiplication of two 4 by 4 matrices
 * @param a the first 4 by 4 matrix
 * @param b the second 4 by 4 matrix
 * @return Matrix44 the resulting matrix from the multiplication operation
 */
Matrix44 matrixMultiplication44_44(Matrix44 a, Matrix44 b);

/**
 * Performs matrix multiplication - premultiplying a 4 by 1 matrix by a 4 by 4 matrix, resulting in a 4 by 1 matrix
 * @param a the first matrix (4 by 4)
 * @param b the second matrix (4 by 1)
 * @return the resulting matrix (4 by 1)
 */
Matrix41 matrixMultiplication44_41(Matrix44 a, Matrix41 b);

/**
 * Creates a 4 by 4 identity matrix
 * @return Matrix44 a 4 by 4 identity matrix
 */
Matrix44 identity44();

/**
 * Determines if two 4 by 4 matrices are equal
 * @param a the first 4 by 4 matrix
 * @param b the second 4 by 4 matrix
 * @return bool the equivalence of the two matrices
 */
bool compareMatrix44(Matrix44 a, Matrix44 b);

/**
 * Determines if two 4 by 1 matrices are equal
 * @param a the first 4 by 1 matrix
 * @param b the second 4 by 1 matrix
 * @return bool the equivalence of the two matrices
 */
bool compareMatrix41(Matrix41 a, Matrix41 b);

/**
 * Determines if either of the two floats are new min/max values, and returns them if they are
 * @param val1 the first float
 * @param val2 the second float
 * @param min updates passed in value with the smallest value from val1 or val2
 * @param max updates passed in value with the greatest value from val1 or val2
 */
void minMax(float val1, float val2, float* min, float* max);

/**
 * Determines if a point and its extension produces a new min or max value
 * @param pos the position of the point on one axis
 * @param len the extension of the point to another point on one axis
 * @param min the address of the current minimum value
 * @param max the address of the current maximum value
 */
void testPointMinMax(float pos, float len, float* min, float* max);

/**
 * Creates a transformation matrix that rotates about a vector rotDeg degrees
 * @param xVec x component of vec
 * @param yVec y component of vec
 * @param zVec z component of vec
 * @param rotDeg degrees of anti-clockwise rotation about vector
 * @return Matrix44 transformation matrix
 */
Matrix44 rotateAboutVec(float xVec, float yVec, float zVec, float rotDeg);

/**
 * Creates a transformation matrix that rotates about the x, y and z axes by xDeg, yDeg and zDeg degrees respectively
 * @param xDeg degrees about x axis
 * @param yDeg degrees about y axis
 * @param zDeg degrees about z axis
 * @return Matrix44 transformation matrix
 */
Matrix44 createRotMat(float xDeg, float yDeg, float zDeg);