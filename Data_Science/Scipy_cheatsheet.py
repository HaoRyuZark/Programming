from scipy.optimize import minimize

##################################################################################################

# Optimization 

def f(x):
    return x**2

res = minimize(f, 2) # find the minimum of the function 

# using x as an array with x[0] = x, x[1] = y, ...
f  = lambda x: (x[0] - 1)**2 + (x[1] - 2.5)**2

# They need to be written in the form function >= 0
contraints = ({'type': "ineq", 'fun': lambda x: x[0]  -2*x[1] + 2}, 
              {'type': "ineq", 'fun': lambda x: -x[0] -2*x[1] + 6}, 
              {'type': "ineq", 'fun': lambda x: -x[0] +2*x[1] + 2}, 
              {'type': "ineq", 'fun': lambda x: x[0]}, 
              {'type': "ineq", 'fun': lambda x: x[1]})

# Bounds of the variables, None is treated as infinity

bounds = ((0, None), (0, None)) 

res = minimize(f, 2, constraints=contraints, bounds=bounds)

##################################################################################################

# Interpolation 

x = [0, 1, 2, 3, 4, 5]
y = [0, 1, 4, 9, 16, 25]

from scipy.interpolate import interp1d

f = interp1d(x, y, kind='cubic') # kind can be 'linear', 'nearest', 'zero', 'slinear', 'quadratic', 'cubic'
xnew = 2.5
ynew = f(xnew) # use interpolation function returned by `interp1d`  
print(ynew)

# Linear interpolation of 2D data

from scipy.interpolate import griddata
import numpy as np

points = np.array([[0, 0], [1, 0], [0, 1], [1, 1]])
values = np.array([0, 1, 1, 0])
grid_x, grid_y = np.mgrid[0:1:5j, 0:1:5j]
grid_z0 = griddata(points, values, (grid_x, grid_y), method='linear')
print(grid_z0)

# Polynimial 

from scipy.interpolate import lagrange
poly = lagrange(x, y)
print(poly(2.5))

##################################################################################################

# Curve Fitting 

from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Define the model function
def model(x, a, b):
    return a * np.exp(b * x)

# Generate synthetic data
xdata = np.linspace(0, 4, 50)
y = model(xdata, 2.5, 1.3)
ydata = y + 0.2 * np.random.normal(size=xdata.size)

# Fit the model to the data
popt, pcov = curve_fit(model, xdata, ydata)
print("Optimal parameters:", popt)

# Plot the data and the fitted curve
plt.scatter(xdata, ydata, label='Data')
plt.plot(xdata, model(xdata, *popt), 'r-', label='Fit: a=%5.3f, b=%5.3f' % tuple(popt))
plt.legend()
plt.show()

##################################################################################################

# Special functions 

from scipy.special import gamma, jn, erf

print("Gamma(5):", gamma(5))  # Gamma function
print("Bessel function J1(2.5):", jn(1, 2.5))  # Bessel function of the first kind
print("Error function erf(1):", erf(1))  # Error function


##################################################################################################

# Derivatives

from scipy.misc import derivative # type: ignore
def g(x):
    return x**3 + 2*x**2 + x

print("Derivative of g at x=1:", derivative(g, 1.0, dx=1e-6))   

##################################################################################################

# Integration

from scipy.integrate import quad, dblquad

# Single integral
result, error = quad(lambda x: x**2, 0, 1)
print("Integral of x^2 from 0 to 1:", result)

# Double integral
result, error = dblquad(lambda x, y: x*y, 0, 1, lambda x: 0, lambda x: 1) # type: ignore

print("Double integral of x*y over [0,1]x[0,1]: ", result)

# Triple integral

from scipy.integrate import tplquad
result, error = tplquad(lambda x, y, z: x*y*z, 0, 1,  # type: ignore
                        lambda x: 0, lambda x: 1, 
                        lambda x, y: 0, lambda x, y: 1)
print("Triple integral of x*y*z over [0,1]x[0,1]x[0,1]: ", result)

##################################################################################################

# Differential Equations

from scipy.integrate import solve_ivp

def dydt(t, y):
    return -2 * y + 1

sol = solve_ivp(dydt, [0, 5], [0], t_eval=np.linspace(0, 5, 100))

plt.plot(sol.t, sol.y[0])
plt.xlabel('Time')
plt.ylabel('y(t)')
plt.title('Solution of dy/dt = -2y + 1') 
##################################################################################################

# Fourier Transform

from scipy.fft import fft, ifft

# Sample signal
x = np.linspace(0, 2*np.pi, 100)
y = np.sin(5*x) + 0.5*np.sin(10*x)

# Compute Fourier Transform
y_fft = fft(y)

# Compute Inverse Fourier Transform
y_ifft = ifft(y_fft)

plt.plot(x, y, label='Original Signal')
plt.plot(x, y_ifft.real, label='Reconstructed Signal', linestyle='--') # type: ignore
plt.legend()
plt.title('Fourier Transform and Inverse')
plt.show()

##################################################################################################

# Linear Algebra

from scipy.linalg import inv, det, eig
import numpy as np

A = np.array([[1, 2], [3, 4]])
A_inv = inv(A)
A_det = det(A)

A_eigvals, A_eigvecs = eig(A) # type: ignore
print("Inverse of A:\n", A_inv)
print("Determinant of A:", A_det)
print("Eigenvalues of A:", A_eigvals)
print("Eigenvectors of A:\n", A_eigvecs)

##################################################################################################

# Statistics

from scipy import stats

data = np.random.normal(loc=0, scale=1, size=1000)
mean = np.mean(data)
std_dev = np.std(data)
kurtosis = stats.kurtosis(data)
skewness = stats.skew(data)

print("Mean:", mean)

##################################################################################################

# Information Theory

from scipy.stats import entropy 

p = np.array([0.1, 0.4, 0.5])
q = np.array([0.2, 0.2, 0.6])   

kl_div = entropy(p, q)

##################################################################################################

# Linear Systems of Equations

from scipy.linalg import solve

A = np.array([[3, 2], [1, 2]])
b = np.array([5, 4])

x = solve(A, b)
print("Solution of the system Ax = b:", x)

