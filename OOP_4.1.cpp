#include "OOP_4.1.header.h"
#include <iostream>
#include <cmath>

using namespace std;




int main()
{
    Vector <bool> a(std::pow(10, 7), 0);

    long long n;
    cout << "Enter count of elements: ";
    cin >> n;

    cout << "Enter elements: \n";
    long long element;
    long long max = LONG_LONG_MIN;
    for (long long i =  0; i < n; i++)
    {
        cin >> element;
        a[element] = 1;
        if(element > max)
            max = element;
    }

    for (long long i = 0; i < max + 1; i++)
    {
        if(a[i] == 1)
        cout << i << " ";
    }

    cin.ignore();
    cin.get();
    return 0;
}