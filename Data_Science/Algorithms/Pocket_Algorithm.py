import numpy as np
from matplotlib import pyplot as plt

def generate_points(N):
    return np.random.rand(N, 2)

def generate_decision_line():
    g = generate_points(2)
    # Properly extract x and y
    x1, y1 = g[0]
    x2, y2 = g[1]
    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1

    def getY(x):
        return m * x + b

    return getY

def getClassedPoints(N):
    np.random.seed(5)
    f = generate_decision_line()
    X = generate_points(N)
    y = np.array([1 if f(x[0]) > x[1] else -1 for x in X])
    # Introduce 10% label noise
    for i in np.random.randint(0, len(y), int(len(y) / 10)):
        y[i] = -y[i]
    return X, y, f

# Perceptron hypothesis
def h(x, w):
    return np.sign(np.dot(w.T, x))

def in_sample_error(X_raw, y, w):
    X = np.column_stack((np.ones(X_raw.shape[0]), X_raw))
    y_pred = np.sign(X @ w)
    return np.mean(y_pred != y)

def pocket(X_raw, y, w_init=None, t=100):
    X = np.column_stack((np.ones(X_raw.shape[0]), X_raw))
    
    if w_init is None:
        w = np.zeros(X.shape[1])
    else:
        w = w_init.copy()

    w_hat = w.copy()
    best_err = in_sample_error(X_raw, y, w_hat)
    
    for _ in range(t):
        for i, x_i in enumerate(X):
            if h(x_i, w) != y[i]:
                w_new = w + y[i] * x_i
                err_new = in_sample_error(X_raw, y, w_new)
                if err_new < best_err:
                    w_hat = w_new.copy()
                    best_err = err_new
                w = w_new
                break
    return w_hat

def p(x_values, w):
    # x_values: array of x coordinates
    return -(w[0] + w[1]*x_values)/w[2]

# Generate data
X, y, f_true = getClassedPoints(20)

# Train perceptron
w_final = pocket(X, y, t=1000)

# Plot data points
plt.scatter(X[:, 0], X[:, 1], c=y, cmap='bwr', edgecolors='k')

# Plot true decision boundary
x_line = np.linspace(0, 1, 100)
plt.plot(x_line, f_true(x_line), 'g--', label='True boundary')

# Plot learned decision boundary
plt.plot(x_line, p(x_line, w_final), 'b-', label='PLA boundary')

plt.xlabel('x1')
plt.ylabel('x2')
plt.legend()
plt.show()
