#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <random>
#include <stdexcept>

class Vector {
   public:
    Vector();
    Vector(size_t n);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    void resize(size_t n);
    size_t size() const;
    void fill_random(double min = 0.0, double max = 1.0);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);

    double& operator[](size_t i);
    double operator[](size_t i) const;

    friend std::istream& operator>>(std::istream& is, Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

   private:
    size_t n_;
    double* data_;
};

#endif  // VECTOR_H
