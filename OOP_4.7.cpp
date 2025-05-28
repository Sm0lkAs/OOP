#include <iostream>

#include "Matrix.h"

int main() {
    const size_t R = 3, C = 4;
    Matrix m(R, C);

    for (size_t i = 0; i < R; ++i) m[i].fill_random(0.0, 10.0);

    std::cout << "Matrix after random filling:\n" << m << std::endl;

    std::cout << "columns of matrix:\n";
    for (size_t j = 0; j < C; ++j) {
        Vector col(R);
        for (size_t i = 0; i < R; ++i) {
            col[i] = m[i][j];
        }
        std::cout << "Column " << j << ": " << col << "\n";
    }
    std::cout << std::endl;

    double s = 2.5;
    std::cout << "m + " << s << ":\n" << (m + s) << std::endl;
    std::cout << "m - " << s << ":\n" << (m - s) << std::endl;
    std::cout << "m * " << s << ":\n" << (m * s) << std::endl;
    std::cout << "m / " << s << ":\n" << (m / s) << std::endl;

    Matrix ma = m;
    ma += s;
    std::cout << "ma += s:\n" << ma << std::endl;
    ma = m;
    ma -= s;
    std::cout << "ma -= s:\n" << ma << std::endl;
    ma = m;
    ma *= s;
    std::cout << "ma *= s:\n" << ma << std::endl;
    ma = m;
    ma /= s;
    std::cout << "ma /= s:\n" << ma << std::endl;

    Matrix A3(3, 3), B3(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        A3[i].fill_random(0, 5);
        B3[i].fill_random(0, 5);
    }
    std::cout << "A3:\n" << A3 << "B3:\n" << B3 << std::endl;
    std::cout << "A3 + B3:\n" << (A3 + B3) << std::endl;
    std::cout << "A3 - B3:\n" << (A3 - B3) << std::endl;
    std::cout << "A3 * B3:\n" << (A3 * B3) << std::endl;

    Matrix mb = A3;
    mb += B3;
    std::cout << "mb += B3:\n" << mb << std::endl;
    mb = A3;
    mb -= B3;
    std::cout << "mb -= B3:\n" << mb << std::endl;
    mb = A3;
    mb *= B3;
    std::cout << "mb *= B3:\n" << mb << std::endl;

    std::cout << "A3 == A3? " << (A3 == A3) << "\n";
    std::cout << "A3 != B3? " << (A3 != B3) << "\n\n";

    std::cout << "A3^T:\n" << A3.transpose() << std::endl;
    std::cout << "A3^2:\n" << A3.pow(2) << std::endl;

    std::cout << "is_square: " << A3.is_square() << "\n";
    std::cout << "is_zero: " << A3.is_zero() << "\n";
    std::cout << "is_identity: " << A3.is_identity() << "\n";
    std::cout << "is_diagonal: " << A3.is_diagonal() << "\n";
    std::cout << "is_symmetric: " << A3.is_symmetric() << "\n";
    std::cout << "is_upper_triangular: " << A3.is_upper_triangular() << "\n";
    std::cout << "is_lower_triangular: " << A3.is_lower_triangular() << "\n";

    std::cin.ignore();
    std::cin.get();

    return 0;
}
