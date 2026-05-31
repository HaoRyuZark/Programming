import numpy as np 
import matplotlib as plt 
import pandas as pd 

class MSD:

    def __init__(self, k_components=3) -> None:
        self.k_components = k_components

    def fit(self, X, D=None):
        if D != None: 
            self.D = D ** 2
            self.n_samples, self.m_components = D.shape
        else:
            self.n_samples, self.m_components = D.shape
            self.D = self._get_D_squared(X)
        
    def _get_D_squared(self, X):
        D = np.zeros((self.n_samples, self.n_samples))

        for i in range(self.n_samples):
            c = X[i]
            j_D = 0
            for j in range(self.n_samples):
                if i != j: 
                    D[i][j_D] = np.linalg.norm(c - X[j])
                j_D += 1
        return D ** 2
    
    def _get_positive_eigvals_eigvecs(self, eigvals, eigvecs):
        idxs_of_positive_eigvals = [i for i in range(len(eigvals)) if eigvals[i] >= 0]

        eigvecs = eigvecs[idxs_of_positive_eigvals] 
        eigvals = eigvals[:, idxs_of_positive_eigvals] 

        return eigvals, eigvecs
        

    def transform(self):
        n = self.n_samples

        H = np.eye(n) - np.outer(np.ones(n), np.ones(n)) * 1/n
        B = H @ self.D @ H 

        eigvals, eigvecs = np.linalg.eigh(B)   

        sorted_idx_eig_vals = np.argsort(eigvals)
        self.sorted_eigvals = eigvals[sorted_idx_eig_vals[::-1]]
        self.sorted_eigvecs = eigvecs = eigvecs[:,sorted_idx_eig_vals[::-1]]

        self.filtered_eigvals, self.filtered_eigvecs = self._get_positive_eigvals_eigvecs(eigvals, eigvecs)
        self.coords = self.filtered_eigvecs[:, self.k_components] @ np.diag(np.sqrt(self.filtered_eigvals[:self.k_components]))
        return self.coords

    def PDME(self):
        return self.sorted_eigvals[:, self.k_components] @ np.diag(np.sqrt(self.sorted_eigvals[:self.k_components]))

     
        


