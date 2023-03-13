import sympy as sp

def kanwarTomarMethod(function, x0, tol, iterMax, beta):
    x = sp.Symbol('x')
    functionSympy = sp.sympify(function)
    df = sp.diff(functionSympy, x)
    xk = x0
    i = 0

    while i < iterMax:
        fxk = sp.N(functionSympy.subs(x,xk))
        d_fxk = sp.N(df.subs(x,xk))
        u = fxk/d_fxk
        xk = xk - (1/(1 + beta*u))*(fxk/d_fxk)
        error = max(abs(functionSympy.subs(x, xk)), abs(xk - (xk - 1 )))
        if(error < tol):  
            break
        i = i + 1
        print(xk)

    return [xk,error,i]


print(kanwarTomarMethod('cos(x) - x', 2.1 , 0.00005 ,500,2))