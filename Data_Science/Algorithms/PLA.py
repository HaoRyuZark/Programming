import numpy as np
import matplotlib.pyplot as plt

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
    

class PLA:

    def __init__(self, n_iters=100) -> None:
        self.n_iters= n_iters

    def _perceptron(self, x, w):
        return np.sign(np.dot(x, w))

    def fit(self, X, y):
        self.X = X 
        self.y = y
        self.n_samples, self.m_features = X.shape

    def transform(self):

        self.w = np.zeros(self.m_features + 1)
        ones = np.ones((self.n_samples, 1))
        X_train = np.hstack((ones, self.X))  

        changed = True

        for t in range(self.n_iters): 

            y_pred = self._perceptron(X_train, self.w)

            for i in range(self.n_samples):

                if y_pred[i] != self.y[i]:
                    self.w = self.w + (self.y[i] * X_train[i])
                    changed = True
                    break

                changed = False

            if not changed:
                break

        return self.w

X, y, f = getClassedPoints(20)

pla = PLA(100)
pla.fit(X, y)
w = pla.transform()


m = - (w[1] / w[2]) 
c = - (w[0] / w[2]) 

plt.figure(figsize=(10,7))
plt.scatter(X[:,0], X[:,1], c=y)
plt.plot(X[:,0], m * X[:, 0] + c)
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.title("AHHHHHH")
plt.grid(True)
