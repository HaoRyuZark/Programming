import numpy as np
import matplotlib.pyplot as plt

# Implementieren Sie hier das Perzeptron

def generate_points(N):
    return np.random.rand(N, 2)


def generate_decision_line():
    g = generate_points(2)
    m = (g[1, 1] - g[1, 0]) / (g[0, 1] - g[0, 0])
    b = g[1, 0] - m * g[0, 0]

    def getY(x):
        return m * x + b

    func = getY
    return func

def getClassedPoints(N):
    np.random.seed(5)
    f = generate_decision_line()
    X = generate_points(N)
    y = np.array([1 if f(X[i, 0]) > X[i, 1] else -1
                  for i in range(X.shape[0])])
    return X, y, f
    
# Perceptron
def h(x, w):
    return np.sign(np.dot(w.T, x))
    
# PLA
def pla(X_raw, y, w_init=None):

    # Weird to do it inside the function, but if that is the task whatever
    X = np.column_stack((np.ones(X_raw.shape[0]), X_raw))
    
    if w_init is None:
        w = np.zeros(X.shape[1])
    else:
        w = w_init.copy()
    
    errors = 0

    for i, x_i in enumerate(X):
        
        y_pred = h(x_i, w)
            
        if y_pred != y[i]:
            w += y[i] * x_i
            errors += 1
            break

    if errors == 0:
        return w
    else:
        return pla(X_raw, y, w)


def p(x_values, w):
    # x_values: array of x coordinates
    return -(w[0] + w[1]*x_values)/w[2]
    

        
X, y, f_true = getClassedPoints(20)

# Train perceptron
w_final = pla(X, y)

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

