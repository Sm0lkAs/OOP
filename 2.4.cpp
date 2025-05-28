#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

list<char> create_unique_list(const list<char>& L1) 
{
    list<char> L2;
    unordered_map<char, size_t> counter;
    
    // Первый проход: подсчёт частот символов
    for (const auto& c : L1) 
    {
        counter[c]++;
    }
    
    // Второй проход: фильтрация уникальных элементов
    for (const auto& c : L1) 
    {
        if (counter[c] == 1) 
        {
            L2.push_back(c);
        }
    }
    
    return L2;
}

int main() 
{
    list<char> L1 = {'a', 'b', 'c', 'a', 'd', 'e', 'b', 'f'};
    
    auto L2 = create_unique_list(L1);
    
    cout << "L2: ";
    for (const auto& c : L2) 
    {
        cout << c << " ";
    }
    cout << endl;
    
    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ

    return 0;
}