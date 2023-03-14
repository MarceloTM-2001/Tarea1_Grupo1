#include <iostream>
#include "funtras.h"
#include "funtras.cpp"  
int main()
{
    int num = 0;
    cout << "Factorial of " << num << " = "
         << factorial_t(num) << endl;

    cout << "Factorial of " << num << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << factorial_t(num) << endl;

    int x = 6;
    cout << "Seno hiperbolico: " << x << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << sinh_t(x) << endl;

    int y = 7;
    cout << "Division: " << 7 << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << divi_t(y) << endl;

    int z = 6;
    cout << "logaritmo natural: " << z << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << ln_t(z) << endl;

    int a1 = 8;
    int a2 = 10;
    cout << "Logartimo con base " << a2 << " y argumento " << a1 << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << log_t(a1, a2) << endl;

    int b = 3;
    cout << "Exponencial: " << b << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << exp_t(b) << endl;

    float c = pi_t / 4;
    cout << "Coseno: " << c << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << cos_t(c) << endl;

    float d = 0;
    cout << "Secante: " << d << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << sec_t(d) << endl;

    int e = 0;
    cout << "Arctan: " << e << " en radianes = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << atan_t(e) << endl;

    int f = 2;
    int g = 3;
    cout << g << " elevado a  " << f << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << power_t(g, f) << endl;

    float h = pi_t / 4;
    cout << "Seno: " << h << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << sin_t(h) << endl;

    float i = pi_t;
    cout << "Cosecante: " << i << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << csc_t(i) << endl;
     
     float index = 3;
     float subradix = 16;
     cout << "Raíz: " << index << " de " << subradix << " = "
          << setprecision(
                 numeric_limits<cpp_dec_float_50>::digits10)
          << root_t(subradix, index) << endl;
          
     cout << "Raíz cuadrada de: " << subradix << " = "
          << setprecision(
                 numeric_limits<cpp_dec_float_50>::digits10)
          << sqrt_t(subradix) << endl;    
     
     float j = 0.7;
     cout << "Arcoseno: " << j << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << asin_t(j) << endl;

     float k = pi_t / 4;
     cout << "Coseno hiperbólico: " << k << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << cosh_t(k) << endl;

     float l = pi_t;
     cout << "Cotangente de: " << l << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << cot_t(l) << endl;

     float o = pi_t;
     cout << "Tangente de: " << o << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << tan_t(l) << endl;

     float p = pi_t;
     cout << "Tangente hiperbólico de: " << p << " = "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << tanh_t(l) << endl;

     return 0;

}
