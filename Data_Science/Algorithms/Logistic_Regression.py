import numpy as np
from matplotlib import pyplot as plt
import math

class Logistic_Regression:

    def __init__(self, n_iters=1000, learning_rate=0.0001):
        self.n_iters = n_iters
        self.learning_rate = learning_rate
        self.weights = None 
        self.bias = None 
    
    def theta(self, X):
        return X.T @ self.weights + self.bias

    def sigmoid(self, theta):
        return 1.0 / (1.0 + np.exp(-theta))
    
    def fit(self, X, y):
        n_samples, n_features = X.shape
        
        for _ in range(self.n_iters):
            
            y_pred = self.sigmoid(self.theta(X))
              
            dw = (1/n_samples) * (X.T @ (y_pred - y)) # vector
            db = (1/n_samples) * np.sum((y_pred - y)) # number

            self.weights = self.weights - (self.learning_rate * dw)
            self.bias = self.bias - (self.learning_rate * db)
        
    def predict(self, X, threshold=0.5):
        y_pred = self.sigmoid(self.theta(X))
        return np.array([0 if y <= threshold else 1 for y in y_pred])
