#include "Vector.h"

#include <algorithm>

Vector::Vector() : n_(0), data_(nullptr) {}

Vector::Vector(size_t n) : n_(n), data_(new double[n]()) {}

Vector::Vector(const Vector& other) : n_(other.n_), data_(new double[n_]) {
    std::copy(other.data_, other.data_ + n_, data_);
}

Vector::Vector(Vector&& other) noexcept : n_(other.n_), data_(other.data_) {
    other.n_ = 0;
    other.data_ = nullptr;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        n_ = other.n_;
        data_ = new double[n_];
        std::copy(other.data_, other.data_ + n_, data_);
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        n_ = other.n_;
        data_ = other.data_;
        other.n_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

Vector::~Vector() { delete[] data_; }

void Vector::resize(size_t n) {
    delete[] data_;
    n_ = n;
    data_ = new double[n_]();
}

size_t Vector::size() const { return n_; }

void Vector::fill_random(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    for (size_t i = 0; i < n_; ++i) data_[i] = dist(gen);
}

Vector Vector::operator+(const Vector& other) const {
    if (n_ != other.n_) throw std::invalid_argument("Dimension mismatch in vector addition");
    Vector result(n_);
    for (size_t i = 0; i < n_; ++i) result.data_[i] = data_[i] + other.data_[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (n_ != other.n_) throw std::invalid_argument("Dimension mismatch in vector subtraction");
    Vector result(n_);
    for (size_t i = 0; i < n_; ++i) result.data_[i] = data_[i] - other.data_[i];
    return result;
}

Vector& Vector::operator+=(const Vector& other) {
    if (n_ != other.n_) throw std::invalid_argument("Dimension mismatch in vector addition");
    for (size_t i = 0; i < n_; ++i) data_[i] += other.data_[i];
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    if (n_ != other.n_) throw std::invalid_argument("Dimension mismatch in vector subtraction");
    for (size_t i = 0; i < n_; ++i) data_[i] -= other.data_[i];
    return *this;
}

double& Vector::operator[](size_t i) {
    if (i >= n_) throw std::out_of_range("Vector index out of range");
    return data_[i];
}

double Vector::operator[](size_t i) const {
    if (i >= n_) throw std::out_of_range("Vector index out of range");
    return data_[i];
}

std::istream& operator>>(std::istream& is, Vector& v) {
    for (size_t i = 0; i < v.n_; ++i) is >> v.data_[i];
    return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (size_t i = 0; i < v.n_; ++i) {
        os << v.data_[i] << (i + 1 < v.n_ ? ", " : "");
    }
    os << "]";
    return os;
}
