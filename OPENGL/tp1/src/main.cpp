#include <iostream>

#include "matrix4.hh"

Matrix4 identity() {
    auto id = Matrix4();
    id.value_set(0, 0, 1);
    id.value_set(1, 1, 1);
    id.value_set(2, 2, 1);
    id.value_set(3, 3, 1);
    return id;
}

int main() {
    auto m = Matrix4();

    int value = 1;
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            if (!m.value_set(i, j, value)) {
                std::cerr << "LOL" << std::endl;
                return 1;
            }
            //value ++;
        }
    }

    auto m2 = Matrix4();

    value = 1;
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            if (!m2.value_set(i, j, value)) {
                std::cerr << "LOL" << std::endl;
                return 1;
            }
        }
    }
    std::cout << m;
    std::cout << m2;

    m *= m2;

    std::cout << m;

    m = identity();

    std::cout << m;
    return 0;
}
