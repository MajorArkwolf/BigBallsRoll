#include "OpenGL.h"
#include "Math/vec3.h"
#include "Math/vectorMath.h"
#include <math.h>

void gluPerspective( GLfloat fovY, GLfloat aspect, GLfloat zNear, GLfloat zFar ) {
    const GLfloat pi = 3.1415926535897932384626433832795f;
    GLfloat fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tanf( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void gluLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ) {
    GLfloat Mat[16] = {0.0f};
    Mat[15] = 1;
    Vec3 forward = Vec3_construct();
    forward.X = centerX - eyeX;
    forward.Y = centerY - eyeY;
    forward.Z = centerZ - eyeZ;
    Vec3 up = Vec3_construct();
    up.X = upX;
    up.Y = upY;
    up.Z = upZ;
    forward = VectorMath_normaliseVec3(&forward);
    Vec3 side = VectorMath_crossProductVec3ByVec3(&forward, &up);
    side = VectorMath_normaliseVec3(&side);
    up = VectorMath_crossProductVec3ByVec3(&side, &forward);
    Mat[0] = side.X;
    Mat[4] = side.Y;
    Mat[8] = side.Z;
    Mat[1] = up.X;
    Mat[5] = up.Y;
    Mat[9] = up.Z;
    Mat[2] = -forward.X;
    Mat[6] = -forward.Y;
    Mat[10] = -forward.Z;
    glLoadMatrixf(Mat);
    glTranslated(-eyeX, -eyeY, -eyeZ);
}

void deregisterLights() {
    for (size_t i = 0; i < 10; ++i) {
        glDisable(GL_LIGHT0 + i);
    }
}
