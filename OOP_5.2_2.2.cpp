#include <iostream>
#include <vector>

void multiplyMatrixVector(int n) {
    std::vector<double> A(n * n);  // Матрица А
    std::vector<double> x(n);      // Вектор x
    std::vector<double> y(n);      // Вектор y
    std::vector<double> c(n);      // Вектор c, результат

    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        y[i] = i + 1;
        for (int j = 0; j < n; ++j) {
            A[i * n + j] = i + j + 1;
            std::cout << A[i * n + j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Vector x: ";
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";  // Выводим вектор x
    }
    std::cout << std::endl;

    std::cout << "Vector y: ";
    for (int i = 0; i < n; ++i) {
        std::cout << y[i] << " ";  // Выводим вектор y
    }
    std::cout << std::endl;

    // Вычисляем c = A * (x + y)
    for (int i = 0; i < n; ++i) {
        c[i] = 0;
        for (int j = 0; j < n; ++j) {
            c[i] += A[i * n + j] * (x[j] + y[j]);
        }
    }

    std::cout << "Vector c: ";
    for (int i = 0; i < n; ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the matrix dimension (n): ";
    std::cin >> n;

    multiplyMatrixVector(n);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
