//
// Created by Marcelo Truque Montero on 10/02/2023.
//

#include "Functions.h"



double divi_t(double x){
    double Xk0;//Es el termino anterior, este es el que se va acumulando y en la formula se expresaa como X(k)
    double eps=2.2204e-16;
    int sign=1;
    if(x<0){
        x*=-1;
        sign*=-1;
    }

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
    return Xk1*sign;//Valor que cumple con la tolerancia o que llegó al máximo de iteracionesC
}


double ln_t(double x){
    if(x<=0){//En caso de que la entrada del logaritmo sea negativa debe dar error (en este caso res -1)
        return -1;
    }
    double number=(x-1)*divi_t(x+1);//Para simplificar código se guarda el cálculo que se repite
    double X0=2*number;//Primera iteración
    double Xk=0;//Variable que guardará futuras iteraciones
    for(int n=1;n<maxiter;n++){
        Xk=X0+(2*number* divi_t((2*n)+1)*pow(number,2*n));//Sumatoria
        if(abs(Xk-X0)<tol){
            break;
        }
        X0=Xk;//No cumple tolerancia se actualiza la iteración anterior para el próximo cálculo
    }
    return Xk;
}

double log_t(double x,double y) {
    if (x <= 0 or y < 0 or (x==1 and y==1)) {//Casos donde el logaritmo se indefine
        return -1;
    } else if (y == 0) {//Caso especial base 0 da siempre 0
        return 0;
    }else{//Caso regular
        return ln_t(x)* divi_t(ln_t(y));
    }
}

long long factorial(int x){
    long long answer=1;//Resultado
    for(x;x>1;x--){
        answer*=x;
    }
    return answer;
}


double sin_t(double x){
    double S0=x;//La primera iteración equivale al número dado en sí
    double Sk=0;
    for(int n=1;n<maxiter;n++){
        long something =tgamma((2*n)+2);//Guardo el factorial por aparte por cuestiones de control a la hora de hacer pruebas
        Sk=S0+(pow(-1,n)*pow(x,(2*n)+1)* divi_t(something));//Siguiente Iteración
        if(abs(Sk-S0)<tol){//Cumple con la tolerancia
            break;
        }
        S0=Sk;//Guardo el valor y continúo iterando
    }
    return Sk;//Devuelvo iteración de mayor precisión

}