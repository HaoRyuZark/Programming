import numpy as np
import matplotlib.pyplot as plt 
from numpy.typing import NDArray
import pandas as pd

class PCA:
    
    def __init__(self, k) -> None:
        self.k = k 
        self.components = None 
        self.mean = None
        self.eig_vecs = np.array([])
        self.eig_vals = np.array([])
        self.pve:NDArray[np.number] = np.array([])

    def fit(self, X):
        
        self.mean = np.mean(X, axis=0)
        
        X_standardize = X - self.mean

        cov = np.cov(X_standardize.T) 

        eig_vals, eig_vecs = np.linalg.eig(cov)

        eig_vecs = eig_vecs.T
        
        sorted_indices = np.argsort(eig_vals)[::-1]
        
        self.eig_vals = eig_vals[sorted_indices]
        self.eig_vecs = eig_vecs[sorted_indices]
        
        self.components = eig_vecs[:self.k]

    def transform(self, X):
        X = X - self.mean 
        return X @ self.components

    
    def my_pve(self):
        self.pve = self.eig_vals / np.sum(self.eig_vals)
        return self.pve

    def cum_pve(self):
        return np.cumsum(self.pve)
