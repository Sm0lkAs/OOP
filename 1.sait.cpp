#include <iostream>
#include <algorithm>
#include <vector>
#include <limits> // Для очистки буфера ввода


using namespace std;

int main()
{
    vector<int> s;
    int x;
    while(cin >> x)
    s.push_back(x);
    
    int k = 0;

    for (int i = 1; i < s.size() - 1; i++)
    {
        if ((s[i] > s[i - 1]) && (s[i] > s[i + 1]))
        {
            k++;
        }

    }
    cout << k;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Tab enter to exit";
    cin.get();

    return 0;
}