import numpy as np

class Logistic_Regression:

    def __init__(self, n_iters=100, learning_rate=0.01, threshold=0.5):
        self.n_iters = n_iters
        self.learning_rate = learning_rate
        self.threshold = threshold

    def fit(self, X, y):
        self.X = X
        self.y = y
        self.n_samples, self.m_features = X.shape
        return self
    
    def _theta(self, X, w, b):
        return X @ w + b

    def _sigmoid(self, z):
        return 1 / (1 + np.exp(-z))

    def transform(self):
        self.w = np.zeros(self.m_features)
        self.b = 0

        for _ in range(self.n_iters):
            z = self._theta(self.X, self.w, self.b) 
            y_pred = self._sigmoid(z)

            error = y_pred - self.y

            dw = (1 / self.n_samples) * self.X.T @ error
            db = (1 / self.n_samples) * np.sum(error)

            self.w -= self.learning_rate * dw
            self.b -= self.learning_rate * db

        return self.w, self.b

    def predict(self, X_test):
        z = self._theta(X_test, self.w, self.b)
        y_pred = self._sigmoid(z)

        return np.where(y_pred >= self.threshold, 1, 0)
