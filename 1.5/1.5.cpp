#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include "Header.h"
//#include "1.5_functions.cpp"

//using FunctionPtr = double (*)(double, double, double);

double const ep = pow(10, -6);

using namespace std;

int main()
{
    double a, b, s1, s2, t1, t2, ds, dt;

    cin >> s1 >> s2 >> ds >> t1 >> t2 >> dt >> a >> b;
    cout << "----------------------------------------- " << endl;
    int n = 10;

    cout << setw(10) << left << "S"
        << setw(15) << left << "T"
        << setw(15) << left << "INT"
        << setw(10) << left << "K_ITER" << endl;

    

    for (double s = s1; s <= s2; s += ds)
    {
        for (double t = t1; t <= t2; t += dt)
        {
            n = 10;
            int k_per = 1;
             double S_0 = find_value_of_integral(function_in_point, a, b, s, t, n);

             n += n/2 ;

             double S_1 = find_value_of_integral(function_in_point, a, b, s, t, n);

             while (abs(S_1 - S_0) > ep)
             {
                 S_0 = S_1;
                 n *= 2;
                 S_1 = find_value_of_integral(function_in_point, a, b, s, t, n);
                 k_per++;

             }

             cout << setw(10) << left << s
                 << setw(15) << left << t
                 << setw(15) << left << S_1
                 << setw(10) << left << k_per << endl;

        }
    }


    cin.ignore(); // Очистка буфера ввода
    cin.get();    // Ожидание нажатия клавиши

    return 0;
}


