// можно было когда-то с булевским массивом
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>

void processSequence(int n) {
    std::set<int> uniqueNumbers;

    for (int i = 0; i < n; ++i) {
        int num = rand() % 10000000 + 1;
        uniqueNumbers.insert(num);
    }

    std::vector<int> sortedNumbers(uniqueNumbers.begin(), uniqueNumbers.end());

    std::cout << "Sorted unique numbers:\n";
    for (int num : sortedNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    srand(time(0));
    int n;
    std::cout << "Enter the number of elements in the sequence: ";
    std::cin >> n;

    processSequence(n);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
