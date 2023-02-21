#include <iostream>
#include "funtras.h"
#include "funtras.cpp"
int main() {
    int num = 30;
    cout << "Factorial of " << num << " = "
    << factorial_t(num);

    int x = 6;
    cout << "Seno hiperbolico: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << sinh_t(x) << endl;

    int y = 7;
    cout << "Division: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << divi_t(y) << endl;

    int z = 6;
    cout << "<logaritmo natural: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << ln_t(z) << endl;

    int a1 = 6;
    int a2 = 8;
    cout << "Logartimo: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << log_t(a1, a2) << endl;

    int b = 6;
    cout << "Exponencial: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << exp_t(b) << endl;

    int c = 45 ;
    cout << "Coseno: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << cos_t(c) << endl;

    int d = 45;
    cout << "Secante: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << sec_t(c) << endl;

    int e = 80;
    cout << "Arctan: "
        << setprecision(
            numeric_limits<cpp_dec_float_50>::digits10)
        << atan_t(e) << endl;
    return 0;
}
