import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt
import scipy as sp 


class LDA: 

    def __init__(self, n_dim=2) -> None:
        self.n_dim= n_dim

    def fit(self, X, y): 
        self.X = X
        self.y = y
        labels = np.unique(y)

        self.n_samples, self,n_features = X.shape
        
        mean = np.mean(self.X, axis=0)
        
        Sw = np.zeros((n_features, n_features))
        Sb = np.zeros((n_features, n_features))
   
        for l in labels:

            class_l = self.X[y == l]
            mean_l = np.mean(class_l, axis=0)
            dif = class_l - mean_l  
            Sw += np.outer(dif.T, dif)

            n_c = class_l.shape[0]
            mean_diff = (mean_l - mean).reshape(n_features, 1)

            Sb += n_c * np.outer(mean_diff, mean_diff.T)

        
        eigen_vecs, eigen_vals = np.linalg.eig(np.linalg.inv(Sw) @ Sb)
        sorted_indxs = np.argsort(eigen_vals)[::-1]

        eigen_vals, eigen_vecs = eigen_vals[sorted_indxs], eigen_vecs[sorted_indxs]
        self.n_components = eigen_vecs[:self.n_dim]
    
    def transform(self, X):
        return X @ self.n_components
    
