#include <iostream>
#include <string>

int romanToInt(const std::string& roman) {
    int value = 0;
    int prevValue = 0;

    int romanValues[256] = {0};
    romanValues['I'] = 1;
    romanValues['V'] = 5;
    romanValues['X'] = 10;
    romanValues['L'] = 50;
    romanValues['C'] = 100;
    romanValues['D'] = 500;
    romanValues['M'] = 1000;

    for (int i = roman.size() - 1; i >= 0; --i) {
        int currentValue = romanValues[roman[i]];
        if (currentValue < prevValue) {
            value -= currentValue;
        } else {
            value += currentValue;
        }
        prevValue = currentValue;
    }

    return value;
}

int main() {
    std::string roman = "MCMXCIV";
    int number = romanToInt(roman);
    std::cout << "Roman number " << roman << " is " << number << std::endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}
