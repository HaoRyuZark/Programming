import numpy as np 
import pandas as pd
import sympy as sp 

from matplotlib import pyplot as plt
from numpy.polynomial import Polynomial

#------------------------------------------- Helper 

def phi4(x):
    return np.array([x, x**2, x**3, x**4])

def expland_features(X) -> np.ndarray:
    n_samples = X.shape[0]
    return np.column_stack((np.ones(n_samples), X))


def get_target_function():
    return Polynomial((1, 2, -1, -2))


def lin_reg(X, y):
    return np.linalg.inv(X.T @ X) @ X.T @ y

def get_data(sigma=0, N=5):
    np.random.seed(3)
    p = Polynomial((1, 2, -1, -2))
    x = np.sort(np.random.random_sample(size=N) * 2 - 1)
    noise = np.random.standard_normal(len(x))
    return x, p(x) + noise*sigma


def e_out(y_target, y_approx, w, k=50, interval=np.linspace(-1, 1)):
    return 1/k * np.sum((y_target(interval) - np.array([y_approx(x, w) for x in interval]))**2)


def get_final_g(x, w):
    return w[0] + w[1]* x

#------------------------------------------- Helper 

sigmas = [0, 0.0001, 0.001, 0.01, 0.5, 1, 2]
vals = []
f = get_target_function()

fig, ax = plt.subplots(2, 4, figsize=(15, 10))

i = 0
j = 0

for sigma in sigmas: 

    X_3_2, y_3_2 = get_data(N=5,sigma=sigma)

    X_t_2 = np.array([phi4(x) for x in X_3_2])
    X_t_ext_2 = expland_features(X_t_2)

    w = lin_reg(X_t_ext_2, y_3_2)
    y_plot = [get_final_g(x, w) for x in X_3_2]

    ax[i, j].scatter(X_3_2, y_3_2, label="Sigma")
    ax[i, j].plot(X_3_2, y_3_2, label="True func")
    ax[i, j].plot(X_3_2, y_plot, color="red", label="Approx")
    ax[i, j].grid()
    ax[i, j].legend()
    ax[i, j].set_xlabel("x")
    ax[i, j].set_ylabel("y")

    j += 1

    if j == 4:
        i += 1
        j = 0

    e = e_out(f, get_final_g, w)
    vals.append(e)
    print(e)

ax[1, 3].plot(sigmas, vals, label="Sigmas")
ax[1, 3].set_xlabel("Sigmas")
ax[1, 3].set_ylabel("E_out")
ax[1, 3].grid()
ax[1, 3].legend()
plt.show()
