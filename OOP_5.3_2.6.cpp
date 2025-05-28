#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    list<double> lst;
    cout << "Enter " << n << " numbers: " << endl;
    for (int i = 0; i < n; ++i) {
        double x;
        cin >> x;
        lst.push_back(x);
    }

    vector<list<double>::iterator> vec;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        vec.push_back(it);
    }

    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = n - 1 - i;
        sum += (*vec[i]) * (*vec[j]);
    }

    cout << "Result : " << sum << endl;

    cin.ignore();
    cin.get();

    return 0;
}