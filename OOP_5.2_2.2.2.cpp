#include <iostream>

void multiplyMatrixVectorWithPointers(int n) {
    double** A = new double*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new double[n];
    }

    double* x = new double[n];  // Вектор x
    double* y = new double[n];  // Вектор y
    double* c = new double[n];  // Вектор c, результат

    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        y[i] = i + 1;
        for (int j = 0; j < n; ++j) {
            A[i][j] = i + j + 1;
            std::cout << A[i][j] << " ";
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

    // Вычисление c = A * (x + y)
    for (int i = 0; i < n; ++i) {
        c[i] = 0;
        for (int j = 0; j < n; ++j) {
            c[i] += A[i][j] * (x[j] + y[j]);
        }
    }

    std::cout << "Vector c: ";
    for (int i = 0; i < n; ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i) {
        delete[] A[i];
    }
    delete[] A;
    delete[] x;
    delete[] y;
    delete[] c;
}

int main() {
    int n;
    std::cout << "Enter the matrix dimension (n): ";
    std::cin >> n;

    multiplyMatrixVectorWithPointers(n);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
