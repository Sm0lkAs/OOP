#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Vector.h"

class Matrix {
   public:
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix();

    void resize(size_t rows, size_t cols);

    Vector& operator[](size_t i);
    const Vector& operator[](size_t i) const;

    const std::string& name() const;

    friend std::istream& operator>>(std::istream& is, Matrix& m);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    Matrix operator+(double s) const;
    Matrix operator-(double s) const;
    Matrix operator*(double s) const;
    Matrix operator/(double s) const;
    Matrix& operator+=(double s);
    Matrix& operator-=(double s);
    Matrix& operator*=(double s);
    Matrix& operator/=(double s);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix transpose() const;
    Matrix pow(unsigned int exp) const;

    bool is_square() const;
    bool is_zero() const;
    bool is_identity() const;
    bool is_diagonal() const;
    bool is_symmetric() const;
    bool is_upper_triangular() const;
    bool is_lower_triangular() const;

   private:
    size_t rows_, cols_;
    Vector* data_;
    std::string name_;
    static size_t counter_;
};

#endif  // MATRIX_H
