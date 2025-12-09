import numpy as np
from matplotlib import pyplot as plt
import math

# Load data
data = np.loadtxt('https://data.bialonski.de/ml/admission-data.txt', delimiter=',')
X, y = np.insert(data[:, :2] / 100, 0, 1, 1), (data[:, 2] - .5) * 2

f_1 = X[:,1]
f_2 = X[:,2]
plt.scatter(f_1, f_2, c=y, cmap='viridis')
N = len(X)

def sm(X, w, y):
    val = 0 
    for i in range(N):
        val = val + (y[i] * X[i] * theta_value(X[i], w, y[i]))
    return val

# Better: rewrite theta to accept y_i as parameter
def theta_value(x, w, y_i):
    return -y_i * np.dot(w, x)
    

def sigma(X, w, y):
    val = np.zeros(3)  # Initialize as vector, not scalar
    for i in range(N):
        theta_i = theta_value(X[i], w, y[i])
        val = val + (y[i] * X[i] * theta_i)
    return val
    
def gradient(w, X, y):
    return (1/N) * sm(X, w, y)

def E_in(X, w, y):
    val = 0    
    for i in range(N):
        val = val + math.log(1 + np.e**theta_value(X[i], w, y[i]))
    return (1 / N) * val

T = 100
eta = 2

def update_weights(w, v_t):
    return w + (eta * v_t)

def gradient_descent(X, y):
    w = np.zeros(3)
    errs = []
    for i in range(1, T):
        errs.append(E_in(X, w, y))
        
        g_t = gradient(w, X, y)
        v_t = -g_t
        
        # Normalize v_t
        v_t_norm = np.linalg.norm(v_t)
        if v_t_norm > 0:  # Avoid division by zero
            v_t = v_t / v_t_norm
        
        w = update_weights(w, v_t)
    
    return (w, errs)

# Run gradient descent
w_final, errors = gradient_descent(X, y)
print("Final weights:", w_final)
print("Final error:", errors[-1])

# Plot error over iterations
plt.figure()
plt.plot(range(1, T), errors)
plt.xlabel('Iteration')
plt.ylabel('E_in')
plt.title('Training Error')
plt.show()
