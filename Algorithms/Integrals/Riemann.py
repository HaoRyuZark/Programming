import numpy as np 

def riemann_sum(f, n, a, b):
    h = (b - a)/n
    s = 0
    for i in range(0, n):
        s+= f(a + (i*h))
    return h*s


