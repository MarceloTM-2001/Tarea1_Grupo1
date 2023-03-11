import numpy as np
from scipy import linalg

"""
Descripcion: Aproximacion de una función f mediante el metodo de Pade
Params f: Funcion que se aproxima
Params m: Grado del polinomio del numerador de la aproximacion de Pade
Params n: Grado del polinomio del denominador de la aproximacion de Pade
x0: valor al cual se le hará la aproximación de f(x0)
"""

def pade_approximant(f, m, n, x0):

    # Taylor series expansion of f(x) around x0
    c = np.array([f(x0 + k) for k in range(m+n+1)])
    
    # Split the coefficients into numerator and denominator
    b = c[:m+1]
    a = c[m+1:]
    
    # Construct the matrix system for solving the Pade approximant
    A = np.zeros((m+n+1, m+n+1))
    for i in range(m+n+1):
        for j in range(m+n+1):
            if i <= j and j <= m:
                A[i,j] = -b[j-i]
            elif i <= j and j > m:
                A[i,j] = a[j-m-1-i]
    
    # Solve the matrix system for the Pade approximant coefficients
    p,q = linalg.solve(A, np.concatenate((np.zeros(m+1), [1])))
    
    # Evaluate the Pade approximant at x0
    return np.polyval(p[::-1], x0) / np.polyval(q[::-1], x0)