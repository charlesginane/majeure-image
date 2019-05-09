#include "matrix4.hh"

Matrix4::Matrix4() : buffer_(std::vector<GLfloat>(16))
{
    for (int i = 0; i < 16; ++i)
        buffer_[i] = 0.0;
}

bool
Matrix4::value_set(int i, int j, GLfloat value) {
    if (i > 3 || j > 3)
        return false;
    buffer_[i + 4 * j] = value;
    return true;

}

GLfloat
Matrix4::value_get(int i, int j) const {
    if (i > 3 || j > 3)
        return 0.0;
    return buffer_[i + 4 * j];
}

void
Matrix4::operator*=(const Matrix4& rmainhs) {
    auto tmp = Matrix4();
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            float res = 0.0;
            for (int k = 0; k < 4; ++k) {
                res += buffer_[k + 4 * j] * rmainhs.buffer_[i + 4 * k];
            }
            tmp.buffer_[i + 4 * j] = res;
        }
    }
    *this = tmp;
}
