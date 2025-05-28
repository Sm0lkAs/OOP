#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <stdexcept>

class BigInt {
   private:
    int* digits;
    int size;
    static const int BASE = 10;

    void resize(int newSize);
    void removeLeadingZeroes();

   public:
    BigInt();
    BigInt(const std::string& num);
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    ~BigInt();

    BigInt operator+(const BigInt& other) const;
    BigInt operator*(int num) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator<<(int shift) const;
    bool operator==(const BigInt& other) const;

    int& operator[](int index);
    int operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend std::istream& operator>>(std::istream& is, BigInt& num);

    BigInt pow(int exponent) const;
};

#endif
