import numpy as np
from matplotlib import pyplot as plt

class Linear_Regression:

    def __init__(self) -> None:
        pass

    def fit(self, X, y):
        self.X= X 
        self.y = y
        self.n_samples, self.m_features = X.shape, 1

    def transform(self):
        X = np.column_stack((np.ones(self.n_samples), self.X))
        self.w = np.linalg.inv(X.T @ X) @ X.T @ self.y
        return self.w

X_2_1, y_2_1 = np.loadtxt('https://data.bialonski.de/ml/franchise-data.txt', delimiter=',', unpack=True)

lg = Linear_Regression()
lg.fit(X_2_1, y_2_1)
w = lg.transform() 


func = lambda x: x * w[1] + w[0]

X_plot = np.linspace(X_2_1.min(), X_2_1.max())
y_plot = [func(x) for x in X_plot]
plt.scatter(X_2_1, y_2_1)
plt.plot(X_plot, y_plot)
plt.grid(True)

