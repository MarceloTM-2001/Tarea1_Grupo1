//
// Created by Marcelo Truque Montero on 10/02/2023.
//

#include "Functions.h"



double divi_t(double x){
    double Xk0;//Es el termino anterior, este es el que se va acumulando y en la formula se expresaa como X(k)
    double eps=2.2204e-16;

    if(9.332622e+157<x){ //El numero equivalente tendrá un resultado equivalente en máquina a 0
        return 0;
    }else if(7.156946e+118<x){ //Para 80!<x<100! se usa eps^15 como X0
        Xk0=pow(eps,15);
    }else if(8.3209871e+81<x) {//Para 60!<x<80! se usa eps^11 como X0
        Xk0 = pow(eps, 11);
    }else if(8.1591528e+47<x){//Para 40!<x<60! se usa eps^8 como X0
        Xk0=pow(eps,8);
    }else if(2.432902e+18<x){//Para 20!<x<40! se usa eps^4 como X0
        Xk0=pow(eps,4);
    }else{//Para 0!<x<20! se usa eps^2 como X0
        Xk0=pow(eps,2);
    }

    double Xk1=0;//Se inicializa el valor en 0 por cuestiones de seguridad
    for (int k=0;k<maxiter;k++) {//Loop con máximo de iteraciones de 2500
        Xk1=Xk0*(2-(x*Xk0));//Se calcula la siguiente iteración (La cual ocupa la anterior) en la fórmula este equivaldría al X(k+1)
        if(abs(Xk1-Xk0)<(tol*abs(Xk1))){//Tolerancia aceptable (10e-8)
            break;
        }
        Xk0=Xk1;//Actualiza el valor anterior para calcular el próximo
    }
    return Xk1;//Valor que cumple con la tolerancia o que llegó al máximo de iteracionesC
}

