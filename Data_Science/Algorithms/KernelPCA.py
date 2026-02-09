import numpy as np 
import pandas as pd 
import math

class Kernel_PCA:

    def __init__(self, k, kernel):
        self.k = k
        self.kernel = kernel

    
    def fit(self, X, y):

        cov = self._center(self._cov(X))

        eig_vecs, eig_vals = np.linalg.eig(cov)

        sorted_indx = np.argsort(eig_vals)

        eig_vecs = eig_vecs[sorted_indx]
        eig_vals = eig_vals[sorted_indx]

        self.components = eig_vecs[::self.k]
        self.eigvals = eig_vals[::self.k]

        self._normalize()
        
    def _center(self, K):
        n = K.shape[0]
        o_n = np.ones((n, n)) 
        return K - (o_n @ K) - (K @ o_n) + (o_n @ K @ o_n)

    def _cov(self, X):
        cov = []

        for x in X:
            row = [] 
            for y in X:
                row.append(self.kernel(x, y))
            cov.append(row)

        return np.array(cov)

    def _normalize(self):
        self.components = np.array([(1/math.sqrt(self.eigvals[i]) * (self.components[i]/ np.linalg.norm(self.components[i]))) for i in range(self.k)])

    def transform(self, X):
        return X @ self.components



    