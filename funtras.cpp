//
// Created by Marcelo Truque Montero on 10/02/2023.
// Updated by Diana Mejias on 14/02/2023.
//

#include "funtras.h"


bool errorflag = false;

/*
Descripcion: Aproximacion de x elevando a la -1 
Params x: corresponde al denominador 
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
sign: corresponde al signo que tomara el resultado
*/
cpp_dec_float_50 divi_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0; // Es el termino anterior, este es el que se va acumulando y en la formula se expresaa como X(k)
    cpp_dec_float_50 eps = 2.2204e-16;
    int sign = 1;
    if (x < 0)
    {
        x *= -1;
        sign *= -1;
    }

    if (9.332622e+157 < x)
    { // El numero equivalente tendrá un resultado equivalente en máquina a 0
        return 0;
    }
    else if (7.156946e+118 < x)
    { // Para 80!<x<100! se usa eps^15 como X0
        s0 = pow(eps, 15);
    }
    else if (8.3209871e+81 < x)
    { // Para 60!<x<80! se usa eps^11 como X0
        s0 = pow(eps, 11);
    }
    else if (8.1591528e+47 < x)
    { // Para 40!<x<60! se usa eps^8 como X0
        s0 = pow(eps, 8);
    }
    else if (2.432902e+18 < x)
    { // Para 20!<x<40! se usa eps^4 como X0
        s0 = pow(eps, 4);
    }
    else
    { // Para 0!<x<20! se usa eps^2 como X0
        s0 = pow(eps, 2);
    }

    cpp_dec_float_50 sk = 0; // Se inicializa el valor en 0 por cuestiones de seguridad
    for (int k = 0; k < iterMax; k++)
    {                                // Loop con máximo de iteraciones de 2500
        sk = s0 * (2 - (x * s0)); // Se calcula la siguiente iteración (La cual ocupa la anterior) en la fórmula este equivaldría al X(k+1)
        if (abs(sk - s0) < (tol * abs(sk)))
        { // Tolerancia aceptable (10e-8)
            break;
        }
        s0 = sk; // Actualiza el valor anterior para calcular el próximo
    }
    return sk * sign; // Valor que cumple con la tolerancia o que llegó al máximo de iteracionesC
}

/*
Descripcion: Aproximacion de logaritmo natural 
Params x: corresponde al argumento del logaritmo
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 ln_t(cpp_dec_float_50 x)
{
    if (x <= 0)
    { // En caso de que la entrada del logaritmo sea negativa debe dar error (en este caso res -1)
        errorflag = true;
        cout << "Logaritmo Indefinido" << endl;
        return -1;
    }
    cpp_dec_float_50 number = (x - 1) * divi_t(x + 1); // Para simplificar código se guarda el cálculo que se repite
    cpp_dec_float_50 X0 = 2 * number;                  // Pirmera iteración
    cpp_dec_float_50 Xk = 0;                           // Variable que guardará futuras iteraciones
    for (int n = 1; n < iterMax; n++)
    {
        Xk = X0 + (2 * number * divi_t((2 * n) + 1) * pow(number, 2 * n)); // Sumatoria
        if (abs(Xk - X0) < tol)
        {
            break;
        }
        X0 = Xk; // No cumple tolerancia se actualiza la iteración anterior para el próximo cálculo
    }
    return Xk;
}

/*
Descripcion: Aproximacion de logaritmo 
Params x: corresponde al argumento del logaritmo
Params y: corresponde a la base del loagaritmo
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 log_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
    if (x <= 0 or y < 0 or (x == 1 and y == 1))
    { // Casos donde el logaritmo se indefine
        errorflag = true;
        cout << "Logaritmo indefinido" << endl;
        return -1;
    }
    else if (y == 0)
    { // Caso especial base 0 da siempre 0
        return 0;
    }
    else
    { // Caso regular
        return ln_t(x) * divi_t(ln_t(y));
    }
}

/*
Descripcion: Factorial de x
Params x: corresponde al exponente de euler
Se determina mediante recursividad
*/
cpp_dec_float_50 factorial_t(int x)
{
    cpp_dec_float_50 fact = 1;
    for (int i = x; i > 1; --i)
        fact *= i;
    return fact;
}

/*
Descripcion: Exponencial euler elevado a la x
Params x: corresponde al exponente de euler
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 exp_t(cpp_dec_float_50 x)
{
    if (x == 0)
    {
        return 0;
    }

    cpp_dec_float_50 s0 = 1;
    cpp_dec_float_50 sk;

    for (int n = 1; n < iterMax; n++)
    {
        sk = s0 + (pow(x, n) * divi_t(factorial_t(n)));
        if (abs(sk - s0) < tol)
        {
            break;
        }
        s0 = sk;
    }
    return sk;
}

/*
Descripcion: Aproximacion de coseno de x 
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 cos_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = 1;
    cpp_dec_float_50 sk;

    for (int n = 1; n < iterMax; n++)
    {
        sk = s0 + pow((-1), n) * pow(x, 2 * n) * divi_t(factorial_t(2 * n));
        if (abs(sk - s0) < tol)
        {
            break;
        }
        s0 = sk;
    }
    return sk;
}

/*
Descripcion: Aproximacion de secante de x 
Params x: corresponde al argumento de la funcion
Se aproxima mediante la equivalencia con coseno.
*/
cpp_dec_float_50 sec_t(cpp_dec_float_50 x)
{
    return 1 * divi_t(cos_t(x));
}

/*
Descripcion: Aproximacion de seno hiperbolico de x 
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 sinh_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = x;
    cpp_dec_float_50 sk;

    for (int n = 1; n < iterMax; n++)
    {
        sk = s0 + pow(x, 2 * n + 1) * divi_t(factorial_t(2 * n + 1));
        if (abs(sk - s0) < tol)
        {
            break;
        }
        s0 = sk;
    }
    return sk;
}

/*
Descripcion: Aproximacion de seno de x 
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 sin_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = x; // La primera iteración equivale al número dado en sí
    cpp_dec_float_50 sk = 0;
    for (int n = 1; n < iterMax; n++)
    {
        sk = s0 + (pow((-1), n) * pow(x, (2 * n) + 1) * divi_t(factorial_t((2 * n) + 2))); // Siguiente Iteración
        if (abs(sk - s0) < tol)
        { // Cumple con la tolerancia
            break;
        }
        s0 = sk; // Guardo el valor y continúo iterando
    }
    return sk; // Devuelvo iteración de mayor precisión
}

/*
Descripcion: Aproximacion de cosecante de x 
Params x: corresponde al argumento de la funcion
Se verifica mediante la equivalencia con seno
*/
cpp_dec_float_50 csc_t(cpp_dec_float_50 x)
{
    if (fmod(x, pi_t) == 0)
    { // Caso de error cuando sen se hace 0 se indefine el csc
        errorflag = true;
        cout << "División por 0" << endl;
        return 0;
    }
    else
    {
        return divi_t(sin_t(x)); // se devuelve el sen(x)^-1
    }
}

/*
Descripcion: Aproximacion de x elevando a la y
Params x: corresponde a la base de la exponencial
Params y: corresponde al exponente de la funcion
Se utilizan propiedades que invlocan funciones de euler y logaritmo natural
*/
cpp_dec_float_50 power_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
    return exp_t(y * ln_t(x));
}

/*
Documentacion pendiente debido a dudas con la funcion
*/
cpp_dec_float_50 atan_t(cpp_dec_float_50 x)
{
    if (x > 1)
    {
        return pi_t * divi_t(2) - atan_t_aux(x);
    }
    else if (x < 1)
    {
        return -pi_t * divi_t(2) - atan_t_aux(x);
    }
}

cpp_dec_float_50 atan_t_aux_firstCase(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = x;
    cpp_dec_float_50 sk;

    for (int n = 0; n < iterMax; n++)
    {
        sk = s0 + pow(-1, n) * pow(x, 2 * n + 1) * divi_t((2 * n + 1) * pow(x, 2 * n + 1));
        if (abs(sk - s0) < tol)
        {
            break;
        }
        s0 = sk;
    }
    return sk;
}

cpp_dec_float_50 atan_t_aux(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = 1 * divi_t(x);
    cpp_dec_float_50 sk;

    for (int n = 0; n < iterMax; n++)
    {
        sk = s0 + pow(-1, n) * divi_t((2 * n + 1) * pow(x, 2 * n + 1));
        if (abs(sk - s0) < tol)
        {
            break;
        }
        s0 = sk;
    }
    return sk;
}

/*
Descripcion: Función que determina si un número entero es par
Params num: numero por analizar
Se resta 2 al numero hasta llegar a cero a -1, en el primer
caso, el numero es par, si no, es impar
*/

bool check_even(cpp_int num)
{
    while (true)
    {
        if (num == -1)
        {
            return false;
        }
        else if (num == 0)
        {
            return true;
        }

        num = num - 2;
    }
}

/*
Descripcion: Aproximacion de la raíz y de x
Params x: corresponde al subradical 
Params y: corresponde al indice de la raiz
Se realiza la validación de los parámetros de entrada
*/

cpp_dec_float_50 root_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
    if (check_even(cpp_int(y)) && (x < 0) | (y == 0))
    {
        errorflag = true;
        cout << "Root not defined" << endl;
        return 0;
    }
    else
    {
        return root_t_aux(x, y);
    }
}

/*
Descripcion: Aproximacion de la raíz y de x
Params x: corresponde al subradical 
Params y: corresponde al indice de la raiz
Se utiliza una aproximación para el cálculo del valor final
*/

cpp_dec_float_50 root_t_aux(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
    cpp_dec_float_50 x0 = x * divi_t(2);
    cpp_dec_float_50 xk;

    for (int n = 0; n < iterMax; n++)
    {
        xk = x0 - ((pow(x0, y) - x) * divi_t(y * pow(x0, y - 1)));
        if (abs(xk - x0) < tol)
        { 
            break;
        }
        x0 = xk;
    }
    return xk;
}

/*
Descripcion: Aproximacion de la raíz cuadrada de x
Params x: corresponde al subradical
Se utiliza la propiedad que define a la raiz como un exponente
*/

cpp_dec_float_50 sqrt_t(cpp_dec_float_50 x)
{
    return root_t(x, 2);
}


/*
Descripcion: Aproximacion del arcoseno de x
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 asin_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = x;
    cpp_dec_float_50 sk = 0;

    for (int n = 1; n < iterMax; n++)
    {
        cpp_dec_float_50 denominator = (pow(4, n) * pow(factorial_t(n), 2) * ((2 * n) + 1));

        sk = s0 + ((factorial_t(2 * n)) * (pow(x, ((2 * n) + 1))) * (divi_t(denominator)));
        if (abs(sk - s0) < tol)
        { 
            break;
        }
        s0 = sk; 
    }
    return sk;
}

/*
Descripcion: Aproximacion del coseno hiperbólico de x
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 cosh_t(cpp_dec_float_50 x)
{
    cpp_dec_float_50 s0 = x;
    cpp_dec_float_50 sk = 0;

    for (int n = 1; n < iterMax; n++)
    {

        sk = s0 + ((pow(x, (2 * n))) * (divi_t(factorial_t(2 * n))));
        if (abs(sk - s0) < tol)
        { 
            break;
        }
        s0 = sk; 
    }
    return sk;
}

/*
Descripcion: Aproximacion de la cotangente de x
Params x: corresponde al argumento de la funcion
s0: valor incial de la aproximacion
sk: suma en la k-esima posicion
*/
cpp_dec_float_50 cot_t(cpp_dec_float_50 x)
{
    return ((cos_t(x)) * (divi_t(sin_t(x))));
}