#include "Matrix.h"

size_t Matrix::counter_ = 0;

Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows),
      cols_(cols),
      data_(new Vector[rows]),
      name_("matrix " + std::to_string(++counter_)) {
    for (size_t i = 0; i < rows_; ++i) data_[i].resize(cols_);
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      data_(new Vector[rows_]),
      name_("matrix " + std::to_string(++counter_)) {
    for (size_t i = 0; i < rows_; ++i) data_[i] = other.data_[i];
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_), name_(std::move(other.name_)) {
    other.data_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new Vector[rows_];
        for (size_t i = 0; i < rows_; ++i) data_[i] = other.data_[i];
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
        name_ = std::move(other.name_);
        other.data_ = nullptr;
    }
    return *this;
}

Matrix::~Matrix() { delete[] data_; }

void Matrix::resize(size_t rows, size_t cols) {
    delete[] data_;
    rows_ = rows;
    cols_ = cols;
    data_ = new Vector[rows_];
    for (size_t i = 0; i < rows_; ++i) data_[i].resize(cols_);
}

Vector& Matrix::operator[](size_t i) {
    if (i >= rows_) throw std::out_of_range("Row index out of range");
    return data_[i];
}

const Vector& Matrix::operator[](size_t i) const {
    if (i >= rows_) throw std::out_of_range("Row index out of range");
    return data_[i];
}

const std::string& Matrix::name() const { return name_; }

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (size_t i = 0; i < m.rows_; ++i)
        for (size_t j = 0; j < m.cols_; ++j) is >> m[i][j];
    return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << m.name() << " (" << m.rows_ << "x" << m.cols_ << "):\n";
    for (size_t i = 0; i < m.rows_; ++i) os << m.data_[i] << "\n";
    return os;
}

Matrix Matrix::operator+(double s) const {
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] + s;
    return r;
}

Matrix Matrix::operator-(double s) const {
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] - s;
    return r;
}

Matrix Matrix::operator*(double s) const {
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] * s;
    return r;
}

Matrix Matrix::operator/(double s) const {
    if (s == 0) throw std::invalid_argument("Division by zero");
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] / s;
    return r;
}

Matrix& Matrix::operator+=(double s) { return *this = *this + s; }
Matrix& Matrix::operator-=(double s) { return *this = *this - s; }
Matrix& Matrix::operator*=(double s) { return *this = *this * s; }
Matrix& Matrix::operator/=(double s) { return *this = *this / s; }

Matrix Matrix::operator+(const Matrix& o) const {
    if (rows_ != o.rows_ || cols_ != o.cols_) throw std::invalid_argument("Dim mismatch");
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] + o.data_[i][j];
    return r;
}

Matrix Matrix::operator-(const Matrix& o) const {
    if (rows_ != o.rows_ || cols_ != o.cols_) throw std::invalid_argument("Dim mismatch");
    Matrix r(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[i][j] = data_[i][j] - o.data_[i][j];
    return r;
}

Matrix Matrix::operator*(const Matrix& o) const {
    if (cols_ != o.rows_) throw std::invalid_argument("Dim mismatch");
    Matrix r(rows_, o.cols_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < o.cols_; ++j)
            for (size_t k = 0; k < cols_; ++k) r[i][j] += data_[i][k] * o.data_[k][j];
    return r;
}

Matrix& Matrix::operator+=(const Matrix& o) { return *this = *this + o; }
Matrix& Matrix::operator-=(const Matrix& o) { return *this = *this - o; }
Matrix& Matrix::operator*=(const Matrix& o) { return *this = *this * o; }

bool Matrix::operator==(const Matrix& o) const {
    if (rows_ != o.rows_ || cols_ != o.cols_) return false;
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            if (std::fabs(data_[i][j] - o.data_[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::operator!=(const Matrix& o) const { return !(*this == o); }

Matrix Matrix::transpose() const {
    Matrix r(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j) r[j][i] = data_[i][j];
    return r;
}

Matrix Matrix::pow(unsigned int exp) const {
    if (!is_square()) throw std::invalid_argument("Not square");
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) result[i][i] = 1.0;
    Matrix base(*this);
    while (exp) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

bool Matrix::is_square() const { return rows_ == cols_; }

bool Matrix::is_zero() const {
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            if (std::fabs(data_[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::is_identity() const {
    if (!is_square()) return false;
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            if ((i == j && std::fabs(data_[i][j] - 1) > 1e-9) ||
                (i != j && std::fabs(data_[i][j]) > 1e-9))
                return false;
    return true;
}

bool Matrix::is_diagonal() const {
    if (!is_square()) return false;
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            if (i != j && std::fabs(data_[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::is_symmetric() const {
    if (!is_square()) return false;
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = i + 1; j < cols_; ++j)
            if (std::fabs(data_[i][j] - data_[j][i]) > 1e-9) return false;
    return true;
}

bool Matrix::is_upper_triangular() const {
    if (!is_square()) return false;
    for (size_t i = 1; i < rows_; ++i)
        for (size_t j = 0; j < i; ++j)
            if (std::fabs(data_[i][j]) > 1e-9) return false;
    return true;
}

bool Matrix::is_lower_triangular() const {
    if (!is_square()) return false;
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = i + 1; j < cols_; ++j)
            if (std::fabs(data_[i][j]) > 1e-9) return false;
    return true;
}
