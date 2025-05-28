#include "bigint.h"

#include <iostream>
#include <stdexcept>
#include <string>

BigInt::BigInt() : size(1) {
    digits = new int[size];
    digits[0] = 0;
}

BigInt::BigInt(const std::string& num) : size(num.size()) {
    digits = new int[size];
    for (int i = 0; i < size; ++i) {
        digits[i] = num[size - 1 - i] - '0';  // Преобразуем символы строки в числа
    }
}

BigInt::BigInt(const BigInt& other) : size(other.size) {
    digits = new int[size];
    for (int i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new int[size];
        for (int i = 0; i < size; ++i) {
            digits[i] = other.digits[i];
        }
    }
    return *this;
}

BigInt::~BigInt() { delete[] digits; }

void BigInt::resize(int newSize) {
    int* newDigits = new int[newSize];
    for (int i = 0; i < std::min(size, newSize); ++i) {
        newDigits[i] = digits[i];
    }
    for (int i = std::min(size, newSize); i < newSize; ++i) {
        newDigits[i] = 0;
    }
    delete[] digits;
    digits = newDigits;
    size = newSize;
}

void BigInt::removeLeadingZeroes() {
    int i = size - 1;
    while (i >= 0 && digits[i] == 0) {
        --i;
    }
    size = i + 1;
    if (size == 0) size = 1;
    resize(size);
}

BigInt BigInt::operator+(const BigInt& other) const {
    int maxSize = std::max(size, other.size) + 1;
    BigInt result;
    result.resize(maxSize);

    int carry = 0;
    for (int i = 0; i < maxSize; ++i) {
        int digitSum = carry;
        if (i < size) digitSum += digits[i];
        if (i < other.size) digitSum += other.digits[i];
        result.digits[i] = digitSum % BASE;
        carry = digitSum / BASE;
    }

    result.removeLeadingZeroes();
    return result;
}

BigInt BigInt::operator*(int num) const {
    BigInt result;
    result.resize(size + 1);
    int carry = 0;

    for (int i = 0; i < size; ++i) {
        int product = digits[i] * num + carry;
        result.digits[i] = product % BASE;
        carry = product / BASE;
    }

    if (carry > 0) {
        result.digits[size] = carry;
    }

    result.removeLeadingZeroes();
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.resize(size + other.size);

    for (int i = 0; i < size; ++i) {
        BigInt temp = other * digits[i];
        result = result + (temp << i);
    }

    result.removeLeadingZeroes();
    return result;
}

BigInt BigInt::operator<<(int shift) const {
    BigInt result = *this;
    result.resize(size + shift);
    for (int i = size - 1; i >= 0; --i) {
        result.digits[i + shift] = result.digits[i];
    }

    for (int i = 0; i < shift; ++i) {
        result.digits[i] = 0;
    }

    return result;
}

bool BigInt::operator==(const BigInt& other) const {
    if (size != other.size) return false;
    for (int i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

int& BigInt::operator[](int index) { return digits[index]; }

int BigInt::operator[](int index) const { return digits[index]; }

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    for (int i = num.size - 1; i >= 0; --i) {
        os << num.digits[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string input;
    is >> input;
    num = BigInt(input);
    return is;
}

BigInt BigInt::pow(int exponent) const {
    BigInt result("1");
    BigInt base = *this;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent /= 2;
    }

    return result;
}
