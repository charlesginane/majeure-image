#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glut.h>

class Matrix4 {

public:
    Matrix4();

    bool value_set(int i, int j, GLfloat value);
    GLfloat value_get(int i, int j) const;

    static Matrix4 identity();
    void operator*=(const Matrix4& rmainhs);

    friend std::ostream& operator<<(std::ostream& out, const Matrix4& m) {
        out << "[";
        for (int j = 0; j < 4; ++j) {
            out << "[ ";
            for (int i = 0; i < 4; ++i) {
                out << m.buffer_[i + 4 * j];
                if (i < 3) {
                    out << ", ";
                }
            }
            out << "]" << std::endl << " ";
        }
        out << "]" << std::endl;
        return out;
    }

private:
    std::vector<GLfloat> buffer_;
};
