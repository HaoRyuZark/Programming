import numpy as np 
import pandas as pd 
import matplotlib.pyplot as pl
from scipy.sparse import data 

class Node:

    def __init__(self, feature_index=None, threshold=None, left=None, right=None, var_red=None, value=None):
        
        # For a non-leaf node
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left 
        self.right = right 
        self.var_red = var_red

        # For the leaf node
        self.value = value 

class Decision_Tree_Regressor:

    def __init__(self, min_samples_split=2, max_depth=2):
        
        self.root = None 
        self.min_samples_split = min_samples_split
        self.max_depth = max_depth


    """
    Rercurive function to create left and right nodes of the tree
    """
    def build_tree(self, dataset, current_depth=0):
        
        X, y = dataset[:,:-1], dataset[:,-1] # X = all cols exept the last, y = only the last col
        n_samples, n_features = X.shape
        
        # Base Case Condition
        if current_depth < self.max_depth and n_samples >= self.min_samples_split:
            
            # Dictionary with data about the best split
            best_split = self.get_best_split(dataset, n_samples, n_features)
            
            # Continue splitting only on impure nodes
            if best_split["var_red"] > 0:
                
                # Rercurive step
                left_subtree = self.build_tree(best_split["dataset_left"], current_depth + 1)
                right_subtree = self.build_tree(best_split["dataset_right"], current_depth + 1)

                # Once the sub trees are build return the current root node 
                return Node(best_split["feature_index"], best_split["threshold"], left_subtree, right_subtree, best_split["var_red"])
        
        # Majority voting for the label
        leaf_value = self.calculate_leaf_value(y)
        
        # return the leaf node
        return Node(value=leaf_value)

    def get_best_split(self, dataset, n_samples, n_features):
        
        best_split = {}
        max_var_red = float("inf")
        
        # Iteratre over all features
        for feature_index in range(n_features):

            feature_values = dataset[:,feature_index]

            # Get possible separations from the values of the feature
            possible_thresholds = np.unique(feature_values) 
            
            # Try all values
            for threshold in possible_thresholds:
                
                # Split based on the current  threshold
                dataset_left, dataset_right = self.split(dataset, feature_index, threshold)
                
                # For non empyt splis proceed to:
                if len(dataset_left) > 0 and len(dataset_right) > 0:
                    
                    # get labels
                    y, left_y, right_y = dataset[:, -1], dataset_left[:, -1], dataset_right[:, -1]
                    
                    # Compute Information gain
                    current_var_red= self.variance_reduction(y, left_y, right_y)
                    
                    # Update best split
                    if current_var_red > max_var_red:
                        best_split["threshold"] = threshold
                        best_split["dataset_right"]  = dataset_right
                        best_split["dataset_left"] = dataset_left
                        best_split["info_gain"] = current_var_red
                        best_split["feature_index"] = feature_index
                        max_var_red = current_var_red


        return best_split

    
    # Split dataset based on the threshold
    def split(self, dataset, feature_index, threshold):

        dataset_left = np.array([row for row in dataset if row[feature_index <= threshold]])
        dataset_right = np.array([row for row in dataset if row[feature_index > threshold]])

        return dataset_left, dataset_right

    def variance_reduction(self, parent, l_child, r_child):
        
        weight_l = len(l_child) / len(parent)
        weight_r = len(r_child) / len(parent)
        
        # Applying mathematical formula
        return np.var(parent) - (weight_l * np.var(l_child) + weight_r  * np.var(r_child))

   
    # Majority voting function
    def calculate_leaf_value(self, y):
        Y = list(y)
        return max(Y, key=Y.count)

    
    def fit(self, X, y):
        dataset = np.concatenate((X, y), axis=1)
        self.root = self.build_tree(dataset, 0)
    
    def predict(self, X):
        return [self.make_prediction(x, self.root) for x in X]
    
    # Binary search like function to find the correspoding class
    def make_prediction(self, x, tree):

        if tree.value != None:
            return tree.value 

        feature_val = x[tree.feature.value]

        if feature_val <= tree.threshold:
            return self.make_prediction(x, tree.left)
        
        else:
            return self.make_prediction(x, tree.right)

from sklearn.model_selection import train_test_split
from sklearn import datasets

data = datasets.load_breast_cancer()


def accuracy(preds, y_test):
    return np.sum(preds == y_test) / len(y_test)

