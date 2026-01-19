import numpy as np 
import Decision_Tree_Classifier

class RandomForest:

    def __init__(self, n_trees=10, max_depth=10, min_sample_split=2, n_features=None):
        self.n_trees = n_trees
        self.max_depth = max_depth 
        self.min_sample_split = min_sample_split 
        self.n_features = n_features
        self.trees = []

    def fit(self, X, y):
        
        for i in range(self.n_trees):
            
            tree = Decision_Tree_Classifier(self.max_depth, self.min_sample_split)
            
            X_sample, y_sample = self._bootstrap_samples(X, y)

            tree.fit(X_sample, y_sample)

            self.trees.append(tree)

    def _bootstrap_samples(self, X, y):
        n_samples = X.shape[0]
        idxs = np.random.choice(n_samples, n_samples, replace=True)
        return X[idxs], y[idxs]

    def predict(self, X):
        return np.array([self.make_prediction(x) for x in X])

    def make_prediction(self, x):
        Y = list([t.make_prediction(x, t.root) for t in self.trees])
        return max(Y, key=Y.count)
        
        


