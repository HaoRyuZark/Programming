from typing import Counter
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as pyplot 
import math 

def euclidean_dist(x,y):
    n = len(x)
    sum = 0
    for i in range(0, n):
        sum += (x[i] - y[i])**2

    return math.sqrt(sum)
     


class KNN:

    def __init__(self, k=3, func=euclidean_dist):
        self.k = k
        self.dis_func =  func

    def fit(self, X, y):
        self.X_train = X 
        self.y_train = y

    def predict(self, X_test):
        predictions = np.array([self._predict(x) for x in X_test])
        return predictions

    def _predict(self, x):

        distances = np.array([self.dis_func(x, n) for n in self.X_train])
        sorted_indices = np.argsort(distances)[::self.k]
 
        k_nearest_labels = [self.y_train[i] for i in sorted_indices]    

        return Counter(k_nearest_labels).most_common() 

        
