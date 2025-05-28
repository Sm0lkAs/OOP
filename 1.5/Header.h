#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//#include "1.5_functions.cpp"
using FunctionPtr = double (*)(double, double, double);
double function_in_point(double x, double s, double t);
double find_value_of_integral(FunctionPtr fun_in_point, double a, double b, double s, double t, int n);

#endif