import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 

"""

- We want to minimize the cost function 
- We assume that we can separate the data linearly 

-> cost(w, b) = 1/N sum[(wX + b - y)^2]

"""

class Linear_Regression:

    def __init__(self, learning_rate=0.001, n_iters=1000):
        self.learning_rate = learning_rate
        self.n_iters = n_iters
        self.weights = None 
        self.bias = None 

    def fit(self, X_train, y_train):
        
        self.weights = np.zeros(X_train.shape[1])
        self.bias = 0
        
        n_samples, n_features = X_train.shape 

        for _ in range(0, self.n_iters):
            
            y_pred = X_train @ self.weights + self.bias 
            
            # Derivatives of the loss function
            dw = (1/n_samples) * (X_train.T @ (y_pred - y_train))
            db = (1/n_samples) * np.sum(y_pred - y_train)

            self.weights = self.weights - self.learning_rate * dw
            self.bias = self.bias - self.learning_rate * db

    def predict(self, X_test):
        y_pred = X_test @ self.weights + self.bias 

        return y_pred

