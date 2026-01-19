import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split

class SVM:

    def __init__(self, learning_rate=0.001, lambda_param=0.01, n_iters=1000):
        self.learning_rate = learning_rate
        self.lambda_param = lambda_param
        self.n_iters = n_iters
        self.w = None 
        self.b = None

    def fit(self, X, y):
        n_samples, n_features = X.shape

        y_ = np.where(y <= 0, -1, 1) # ensuring binary classes 
        self.w = np.zeros(n_features)
        self.b = 0

        for _ in range(self.n_iters):
            for idx, x_i in enumerate(X):

                condition = y_[idx] * (np.dot(x_i, self.w) - self.b) >= 1

                if condition:
                    self.w -= self.learning_rate * (2 * self.lambda_param * self.w) 
                else:
                    self.w -= self.learning_rate * (2 * self.lambda_param * self.w - np.dot(x_i, y_[idx])) 
                    self.b -= self.learning_rate * y_[idx]


    
    def predict(self, X):
        approx = X @ self.w  - self.b
        return np.sign(approx)


X, y = make_blobs(n_samples=100, n_features=2, centers=2, cluster_std=3.5, random_state=42) # type: ignore

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)

svm = SVM()

svm.fit(X_train, y_train)

p = svm.predict(X_test)


