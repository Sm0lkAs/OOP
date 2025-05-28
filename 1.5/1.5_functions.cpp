//#include "1,6.cpp"
#include "Header.h"
#include <cmath>
#include <algorithm>

//using FunctionPtr = double (*)(double, double, double);

double function_in_point(double x, double s, double t)
{
	double y = t * atan(pow(x, 1.0 / 5)) / (x * x + s * sin(x));
	return y;
}

double find_value_of_integral(FunctionPtr fun_in_point, double a, double b, double s, double t, int n)
{
	double INTEGRAL = 0;
	double dx = (b - a) / n;
	for (double i = a; i < b; i += dx)
	{
		INTEGRAL += function_in_point(i, s, t) * dx;

	}
	return INTEGRAL;
}