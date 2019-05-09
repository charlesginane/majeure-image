#include "fructum.hh"

void frustum(Matrix4& mat,
        const GLfloat& left, const GLfloat& right,
        const GLfloat& bottom, const GLfloat& top,
        const GLfloat& z_near, const GLfloat& z_far)
{
    mat.value_set(0, 0, (2 * z_near) / (right - left));
    mat.value_set(0, 2, (right + left) / (right - left));
    mat.value_set(1, 1, (2 * z_near) / (top - bottom));
    mat.value_set(1, 2, (top + bottom) / (top - bottom));
    mat.value_set(2, 2, -1 * ((z_far + z_near) / (z_far - z_near)));
    mat.value_set(2, 3, -1 * ((2 * z_far * z_near) / (z_far - z_near)));
    mat.value_set(3, 2, -1);
}

void look_at(Matrix4& mat,
        const GLfloat& eyeX, const GLfloat& eyeY, const GLfloat& eyeZ,
        const GLfloat& centerX, const GLfloat& centerY, const GLfloat& centerZ,
        GLfloat upX, GLfloat upY, GLfloat upZ)
{
    auto F = vector::Vector3(centerX - eyeX, centerY - eyeY, centerZ - eyeZ);
    auto UP = vector::Vector3(upX, upY, upZ);

    auto f = F.normalize();
    auto up = UP.normalize();

    auto s = f.cross_product(up);
    auto u = (s.normalize()).cross_product(f);

    mat.value_set(0, 0, s.x_get());
    mat.value_set(0, 1, s.y_get());
    mat.value_set(0, 2, s.z_get());

    mat.value_set(1, 0, u.x_get());
    mat.value_set(1, 1, u.y_get());
    mat.value_set(1, 2, u.z_get());

    mat.value_set(2, 0, -1 * f.x_get());
    mat.value_set(2, 1, -1 * f.y_get());
    mat.value_set(2, 2, -1 * f.z_get());

    mat.value_set(3, 3, 1.0);
}
