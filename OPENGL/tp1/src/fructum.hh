#include "matrix4.hh"
#include "vector3.hh"

#include <GL/glut.h>


void frustum(Matrix4& mat,
        const GLfloat& left, const GLfloat& right,
        const GLfloat& bottom, const GLfloat& top,
        const GLfloat& z_near, const GLfloat& z_far);

void look_at(Matrix4& mat,
        const GLfloat& eyeX, const GLfloat& eyeY, const GLfloat& eyeZ,
        const GLfloat& centerX, const GLfloat& centerY, const GLfloat& centerZ,
        GLfloat upX, GLfloat upY, GLfloat upZ);
