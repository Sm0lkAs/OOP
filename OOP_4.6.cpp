#include <iostream>

#include "bigint.h"

int main() {
    // Пример вычисления (178710937610)^3
    BigInt num1("178710937610");

    BigInt result = num1.pow(3);
    std::cout << "Result: " << result << std::endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}
