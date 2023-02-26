//
// Created by Marcelo Truque Montero on 10/02/2023.
//

#ifndef TAREA1_GRUPO1_FUNCTIONS_H
#define TAREA1_GRUPO1_FUNCTIONS_H
#include "iostream"
#include "math.h"
#include <string>
#include "boost/multiprecision/cpp_dec_float.hpp"
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;
using boost::multiprecision::cpp_dec_float_50;

const int iterMax = 2500;
const double tol = 10e-8;
const double pi_t = 3.14159265358979323846;

cpp_dec_float_50 divi_t(cpp_dec_float_50 x);

cpp_dec_float_50 ln_t(cpp_dec_float_50 x);

cpp_dec_float_50 log_t(cpp_dec_float_50 x, cpp_dec_float_50 y);

cpp_dec_float_50 atan_t(cpp_dec_float_50 x);

cpp_dec_float_50 sinh_t(cpp_dec_float_50 x);

cpp_dec_float_50 exp_t(cpp_dec_float_50 x);

cpp_dec_float_50 factorial_t(int x);

cpp_dec_float_50 atan_t_aux(cpp_dec_float_50 x);

cpp_dec_float_50 atan_t_aux_firstCase(cpp_dec_float_50 x);

cpp_dec_float_50 sec_t(cpp_dec_float_50 x);

cpp_dec_float_50 cos_t(cpp_dec_float_50 x);

cpp_dec_float_50 csc_t(cpp_dec_float_50 x);

cpp_dec_float_50 sin_t(cpp_dec_float_50 x);

cpp_dec_float_50 power_t(cpp_dec_float_50 x, cpp_dec_float_50 y);

bool check_even(cpp_int num);

cpp_dec_float_50 root_t(cpp_dec_float_50 x, cpp_dec_float_50 y);

cpp_dec_float_50 root_t_aux(cpp_dec_float_50 x, cpp_dec_float_50 y);

cpp_dec_float_50 sqrt_t(cpp_dec_float_50 x);

cpp_dec_float_50 asin_t(cpp_dec_float_50 x);

cpp_dec_float_50 cosh_t(cpp_dec_float_50 x);

#endif //TAREA1_GRUPO1_FUNCTIONS_H
