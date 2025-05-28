#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <iostream>

// using namespace std;

// #define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Для работы с кодовыми страницами

#include <locale>

using std::cin;
using std::exp;

using std::abs;
using std::cout;
using std::endl;
using std::left;
using std::pow;
using std::right;
using std::setfill;
using std::setw;

using FunctionPtr = double (*)(double, double);
void find_x_by_1(FunctionPtr fun, double e = pow(10, -6), double a = 1, double b = 3,
                 double s1 = 0.1, double s2 = 1.3, double ds = 0.3);
double function_y(double x, double s);

int main() {
    SetConsoleOutputCP(65001);  // Устанавливаем кодовую страницу для вывода
    SetConsoleCP(65001);        // Устанавливаем кодовую страницу для ввода
    setlocale(LC_ALL, "ru_RU.UTF-8");

    find_x_by_1(function_y);

    // cin.ignore(); // Очистка буфера ввода
    std::cin.get();  // Ожидание нажатия клавиши

    return 0;
}

/*void find_x_by_1(double e, double a, double b, double s1, double s2, double ds)
{
        //double s = 0;
        double x = (a + b) / 2;
        double y;
    double a1 = a;
    double b1 = b;

    cout << setw(10) << " S " << " X " << " F(X) " << " K_ITER " << endl;
    for (double s = s1; s < s2; s+=ds)
    {
        int k_iter = 0;
        while (abs(function_y(x, s)) > e)
        {
            if (function_y(x, s) * function_y(a, s) < 0)
                {
                    b1 = x;
                    x = (a1 + b1) / 2;
                }
                else
                {
                    a1 = x;
                    x = (a1 + b1) / 2;
                }
                k_iter++;
        }

        cout << setw(10) << s << " " << x << " " << function_y(x, s) << " " << k_iter << endl;


    }

        //cout << "x = " << x << " f(x) = " << function_y(x, s);
        //return x;
}
*/
double function_y(double x, double s) {
    double y = exp((-s) * x) - 2 + pow(x, 2);
    return y;
}

void find_x_by_1(FunctionPtr fun, double e, double a, double b, double s1, double s2, double ds) {
    double x = (a + b) / 2;
    double y;

    // Заголовок таблицы
    cout << setw(10) << left << "S" << setw(15) << left << "X" << setw(15) << left << "F(X)"
         << setw(10) << left << "K_ITER" << endl;

    // Разделительная линия
    cout << setfill('-') << setw(50) << "-" << endl;
    cout << setfill(' ');  // Сбрасываем заполнение пробелами

    // Вывод данных
    for (double s = s1; s <= s2; s += ds) {
        double a1 = a;
        double b1 = b;

        int k_iter = 0;
        while (abs(fun(x, s)) > e) {
            if (fun(x, s) * fun(a1, s) < 0) {
                b1 = x;
                x = (a1 + b1) / 2;
            } else {
                a1 = x;
                x = (a1 + b1) / 2;
            }
            k_iter++;
        }

        // Вывод строки таблицы
        cout << setw(10) << left << s << setw(15) << left << x << setw(15) << left << fun(x, s)
             << setw(10) << left << k_iter << endl;
    }
}