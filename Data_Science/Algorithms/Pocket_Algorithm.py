import numpy as np
from matplotlib import pyplot as plt

# -------------- START - helper functions --------------

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


# This function creates an "unknown" target function f.
# f is then used to create labels y for points X.
# Some of these labels are randomly flipped to render
# the dataset not linearly separable any more.
# X is a matrix containing N rows (the data points) of
# with 2 dimensions (columns) each.
def getClassedPoints(N):
    np.random.seed(5)
    f = generate_decision_line()
    X = generate_points(N)
    y = np.array([1 if f(X[i, 0]) > X[i, 1] else -1
                  for i in range(X.shape[0])])
    for i in np.random.randint(0, len(y), int(len(y) / 10)):
        y[i] = y[i] * (-1)
    return X, y, f


# -------------- END - helper functions --------------

# Obtain data
X_2_2, y_2_2, f = getClassedPoints(50)

# Visualize data
plt.scatter(X_2_2[:, 0], X_2_2[:, 1], c=y_2_2)

class Pocket:

    def __init__(self, n_iters=100) -> None:
        self.n_iters = n_iters

    def fit(self, X, y) -> None: 
        self.X = X 
        self.y = y 
        self.n_samples, self.m_features = X.shape

    def _perceptron(self, x, w) -> np.ndarray:
        return np.sign(np.dot(x, w))

    def _e_in(self, y_pred) -> np.float64:
        return np.mean(y_pred != self.y)

    def transform(self) -> np.ndarray:

        self.w = np.zeros(self.m_features + 1)
        X_b = np.column_stack((np.ones(self.n_samples), self.X))

        changed = False
        e_in = np.inf
        w_best = self.w

        for t in range(self.n_iters):

            y_pred = self._perceptron(X_b, self.w)
            c_e_in = self._e_in(y_pred)

            if c_e_in < e_in:
               w_best = np.copy(self.w) 
               e_in = c_e_in

            for i in range(self.n_samples):

                if y_pred[i] != self.y[i]:
                    changed = True
                    self.w = self.w + (self.y[i] * X_b[i])
                    break
                changed = False

            if not changed:
                break

        return w_best

p = Pocket(100)
p.fit(X_2_2, y_2_2)
w = p.transform()

plt.scatter(X_2_2[:,0], X_2_2[:,1], c=y_2_2)
plt.plot(X_2_2[:,0], [(-w[1]/w[2])* x - (w[0]/w[2]) for x in X_2_2[:, 0]])
plt.grid(True)
plt.show()
