#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void gluPerspective( GLfloat fovY, GLfloat aspect, GLfloat zNear, GLfloat zFar );

void gluLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);
