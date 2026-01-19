import numpy as np 
import pandas as pd 
import matplotlib.pyplot as pl
from pandas.core.generic import dt
from scipy.sparse import data 

class Node:

    def __init__(self, feature_index=None, threshold=None, left=None, right=None, info_gain=None, value=None):
        
        # For a non-leaf node
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left 
        self.right = right 
        self.info_gain = info_gain

        # For the leaf node
        self.value = value 

class Decision_Tree_Classifier:

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
            if best_split["info_gain"] > 0:
                
                # Rercurive step
                left_subtree = self.build_tree(best_split["dataset_left"], current_depth + 1)
                right_subtree = self.build_tree(best_split["dataset_right"], current_depth + 1)

                # Once the sub trees are build return the current root node 
                return Node(best_split["feature_index"], best_split["threshold"], left_subtree, right_subtree, best_split["info_gain"])
        
        # Majority voting for the label
        leaf_value = self.calculate_leaf_value(y)
        
        # return the leaf node
        return Node(value=leaf_value)

    def get_best_split(self, dataset, n_samples, n_features):
        
        best_split = {}
        max_info_gain = float("inf")
        
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
                    current_info_gain = self.info_gain(y, left_y, right_y, "gini")
                    
                    # Update best split
                    if current_info_gain > max_info_gain:
                        best_split["threshold"] = threshold
                        best_split["dataset_right"]  = dataset_right
                        best_split["dataset_left"] = dataset_left
                        best_split["info_gain"] = current_info_gain
                        best_split["feature_index"] = feature_index
                        max_info_gain = current_info_gain


        return best_split

    
    # Split dataset based on the threshold
    def split(self, dataset, feature_index, threshold):

        dataset_left = np.array([row for row in dataset if row[feature_index <= threshold]])
        dataset_right = np.array([row for row in dataset if row[feature_index > threshold]])

        return dataset_left, dataset_right

    def info_gain(self, parent, l_child, r_child, mode="gini"):
        
        weight_l = len(l_child) / len(parent)
        weight_r = len(r_child) / len(parent)
        
        # Applying mathematical formulas
        if mode == "gini":
            return self.gini_index(parent) - (weight_l * self.gini_index(l_child) + weight_r  * self.gini_index(r_child))

        return self.entropy(parent) - (weight_l * self.entropy(l_child) + weight_r  * self.entropy(r_child))

    """
    Helper for Gini Impurity and Entropy
    """
    def gini_index(self, y):
        
        class_labels = np.unique(y) 
        gini = 0

        for cls in class_labels:
            p_clss = len(y[y == cls]) / len(y) # probability calculation
            gini += p_clss**2

        return gini

    def entropy(self, y):
        class_labels = np.unique(y) 
        entropy = 0

        for cls in class_labels:
            p_clss = len(y[y == cls]) / len(y) # probability calculation
            entropy += p_clss * np.log2(p_clss)

        return entropy

    
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
X, y = data.data, data.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1234)


dtc = Decision_Tree_Classifier(4, 10)

dtc.fit(X_train, y_train)
predictions = dtc.predict(X_test)

def accuracy(preds, y_test):
    return np.sum(preds == y_test) / len(y_test)

print(accuracy(predictions, y_test))
