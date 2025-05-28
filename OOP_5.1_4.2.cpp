#include <cmath>
#include <iostream>
#include <string>

void binaryToHex(const std::string& binary) {
    int integerPart = 0;
    double fractionalPart = 0.0;
    size_t i = 0;

    while (i < binary.size() && binary[i] != '.') {
        integerPart = integerPart * 2 + (binary[i] - '0');
        ++i;
    }

    if (i < binary.size()) i++;
    double base = 0.5;
    while (i < binary.size()) {
        if (binary[i] == '1') {
            fractionalPart += base;
        }
        base /= 2;
        ++i;
    }

    std::cout << "In hexadecimal system: ";
    std::string hexInteger;
    while (integerPart > 0) {
        int remainder = integerPart % 16;
        if (remainder < 10)
            hexInteger = char('0' + remainder) + hexInteger;
        else
            hexInteger = char('A' + (remainder - 10)) + hexInteger;
        integerPart /= 16;
    }
    std::cout << (hexInteger.empty() ? "0" : hexInteger);

    std::cout << ".";
    for (int j = 0; j < 5; ++j) {
        fractionalPart *= 16;
        int integerFractional = static_cast<int>(fractionalPart);
        if (integerFractional < 10) {
            std::cout << integerFractional;
        } else {
            std::cout << (char)('A' + (integerFractional - 10));
        }
        fractionalPart -= integerFractional;
    }

    std::cout << std::endl;
}

int main() {
    std::string binary = "1010.1101";
    binaryToHex(binary);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
