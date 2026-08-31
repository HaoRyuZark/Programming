import numpy as np

class Node: 
    def __init__(self, impurity_value=np.inf, left=None, right=None, indxs=None, feature_index=-1, is_leaf=False) -> None:
        self.impurity_value = impurity_value
        self.left = left
        self.right = right 
        self.indxs = indxs
        self.feature_index = feature_index
        self.is_leaf = is_leaf


class Decision_Tree_Classifier:
    def __init__(self, max_depth=100, min_split_size=2) -> None:
        self.max_depth = max_depth
        self.min_split_size = min_split_size
        self.root = None

    def __entropy(self, y):
        vals, freqs = np.unique(y, return_counts=True)
        l = len(y)
        return np.sum([ -(freqs[i]/l) * np.log2((freqs[i]/l)) for i in range(l)])
        
    def __information_gain(self, X, y, threshold):
        left_idxs, right_idxs = np.where(X < threshold), np.where(X >= threshold)
        y_left, y_right = y[left_idxs], y[right_idxs]
        y_size = len(y)
        return self.__entropy(y) + -((len(y_left)/y_size) * self.__entropy(y_left) + -((len(y_left)/y_size) * self.__entropy(y_left)))

    def fit(self, X, y):
        self.n_samples, self.n_features = X.shape
        self.X = X 
        self.y = y
        
    def transform(self):
        self.root = self.__build_tree(self.X, self.y)

    def __build_tree(self, X, y, current_depth=0):

        n_samples, m_features = X.shape
        node = Node() 

        if current_depth < self.max_depth or n_samples >= self.min_split_size:
            
            best_split = self.__get_best_split()
            
            X_left, X_right = best_split["left"], best_split["right"]
            y_left, y_right = best_split["left"], best_split["right"]
                        
            node.left = self.__build_tree(X_left, y_left)
            node.right= self.__build_tree(X_right, y_right)
            
            node.indxs = None
            return Node 

        node.indxs = X
        
        return node

    def __get_best_split(self):
        pass




