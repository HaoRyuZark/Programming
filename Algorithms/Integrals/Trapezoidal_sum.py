import numpy as np 
import matplotlib.pyplot as plt

TRUE_VAL = np.arctan(1) - np.arctan(0)

def f(x):
    return 1/(1 + x**2)

def trapezoid_sum(f, n , a, b):
    h = (b - a)/n
    s = 0
    for i in range(1, n):
        s+= f(a + (i*h))
    return h/2 * (f(a) + (2*s) + f(b))


def get_vals_and_errors(n, f, a, b, true_val=TRUE_VAL):
    
    errors = np.zeros(n)
    vals = np.zeros(n)

    for i in range(n):
        vals[i] = trapezoid_sum(f, i + 1, a, b)
        errors[i] = abs(vals[i]- true_val)

    return vals, errors

n = 8
a = 0 
b = 1 


print(f'True value of the integral: {TRUE_VAL}')

x = np.arange(1, n+1)
y, y_err = get_vals_and_errors(n, f, a, b)

plt.plot(x, y, color='purple', label='Trapez Sum')
plt.plot(x, y_err, color='red', label='Absolute Error')
plt.plot(x, np.full(len(x), TRUE_VAL), color='blue', label='True Val')
plt.xlabel("Number of Trapezoids")
plt.ylabel("y")
plt.title("Trapezoidal Sum Approximation")
plt.legend(loc='best')
plt.grid(True)
plt.show()

