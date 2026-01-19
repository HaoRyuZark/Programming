import numpy as np
import matplotlib.pyplot as plt 
import pandas as pd

class PCA:
    
    def __init__(self, k) -> None:
        self.k = k 
        self.components = None 
        self.mean = None

    def fit(self, X):
        
        self.mean = np.mean(X, axis=0)
        
        X_standardize = X - self.mean

        cov = np.cov(X_standardize.T) 

        eigval, eigvec = np.linalg.eig(cov)

        eigvec = eigvec.T
        
        sorted_indices = np.argsort(eigval)[::-1]
        
        eigval = eigval[sorted_indices]
        eigvec = eigvec[sorted_indices]
        
        self.components = eigvec[:self.k]

    def transform(self, X):
        X = X - self.mean 
        return X @ self.components



