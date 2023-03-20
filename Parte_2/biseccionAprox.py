
P = 3000
R = 8.3145
T = 300
a = 3.46*10**-3
b = 23.71*10**-6
n = 8

x0 = 6
x1 = 10
tol = 10**-5
iterMax = 1500

f = lambda x: (P + a * (n/x)**2) * ((x/n) - b) - R * T


def biseccion(x0, x1, f, tol, iterMax):
    xk=1
    error=1
    k=1
    if f(x0)*f(x1) < 0:
        while (k != iterMax) and error > tol:
            xk=(x0+x1)/2
            if f(x0)*f(xk) < 0:
                x1=xk
            else:
                x0=xk
            error=abs(f(xk))
            k += 1
    else:
        xk='N/A'
        error='N/A'
        k='N/A'
    return [xk, error, k]

print(biseccion(x0, x1, f, tol, iterMax))