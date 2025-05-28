#include <iostream>
using namespace std;

#include <windows.h> // Для работы с кодовыми страницами
#include <locale>

int main() 
{
    SetConsoleOutputCP(65001); // Установка кодовой страницы
    SetConsoleCP(65001); // Установка кодовой страницы
    setlocale(LC_ALL, "ru_RU.UTF-8");

    

    
    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ

    return 0;
}
