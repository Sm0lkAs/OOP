#include "OOP_4.4.h"

#include <iostream>

using namespace std;

int main() {
    LetterSet set1("abcde");
    LetterSet set2("cdefg");

    cout << "Set1: " << set1 << endl;
    cout << "Set2: " << set2 << endl;

    // +
    LetterSet unionSet = set1 + set2;
    cout << "Union (set1 + set2): " << unionSet << endl;

    // *
    LetterSet intersectionSet = set1 * set2;
    cout << "Intersection (set1 * set2): " << intersectionSet << endl;

    // -
    LetterSet differenceSet = set1 - set2;
    cout << "Difference (set1 - set2): " << differenceSet << endl;

    // +=
    set1 += 'z';
    cout << "After adding 'z' to set1: " << set1 << endl;

    // -=
    set2 -= 'd';
    cout << "After removing 'd' from set2: " << set2 << endl;

    LetterSet set3;
    cout << "Enter a set of letters: ";
    cin >> set3;
    cout << "You entered: " << set3 << endl;

    return 0;
}
