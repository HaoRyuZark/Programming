import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans as km

class KMeans:

    def __init__(self, K=5, n_iters=100, plot_steps=False):        
        self.K = K
        self.n_iters = n_iters
        self.plot_steps = plot_steps
        self.clusters = [[] for _ in range(self.K)] # list of list of indices for each cluster
        self.centroids = [] 

    def trasform(self, X):

        self.X = X
        self.n_samples, self.n_features = self.X.shape

        # Choose some random indices from our samples
        random_samples_indx = np.random.choice(self.n_samples, self.K, replace=False)

        # Choose the current data point as the centroid
        self.centroids = [self.X[idx] for idx in random_samples_indx]

        # Iterative process
        for _ in range(self.n_iters):

            # assign samples to the centroids 
            self.clusters = self.create_clusters()

            if self.plot_steps:
                self.plot()

            # Update centroids
            centroids_old = np.copy(self.centroids)
            self.centroids = self._get_centroids(self.clusters)

            if self._is_converged(centroids_old, self.centroids):
                break 
            
            if self.plot_steps:
                self.plot()


        return self._get_clusters_labels(self.clusters)

    def create_clusters(self):
        clusters = [[] for _ in range(self.K)]

        for idx in range(self.n_samples):
            centroid_idx = self._closest_centroid(idx)
            clusters[centroid_idx].append(idx)
        
        return clusters

    def _closest_centroid(self, idx):       
        return np.argmin(np.linalg.norm(self.centroids - self.X[idx], axis=1))

    def _get_centroids(self, clusters):

        # assign mean value of the clusters to the centroids 
        centroids = np.zeros((self.K, self.n_features))

        for cluster_idx, cluster in enumerate(clusters):
            
            if cluster:
                cluster_mean = np.mean(self.X[cluster], axis=0)
            else:
                cluster_mean = self.X[np.random.choice(self.n_samples)]

            centroids[cluster_idx] = cluster_mean
        return centroids


    def _is_converged(self, centroids_old, centroids_new):
        return np.allclose(centroids_new, centroids_old, atol=1e-6)

    def _get_clusters_labels(self, clusters):

        # each sample will get the label of the cluster it was assigned to 
        labels = np.empty(self.n_samples)

        # For each cluster
        for cluster_idx, cluster in enumerate(clusters):
            # assign the correspoiding cluster to the sample
            for sample_idx in cluster:
                labels[sample_idx] = cluster_idx

        return labels

    def plot(self):

        fig, ax = plt.subplots(figsize=(12,8))

        for i, index in enumerate(self.clusters):
            point = self.X[i].T
            ax.scatter(*point)

        for point in self.centroids:
            ax.scatter(*point, marker="X", color="black", linewidth=2)

        plt.show()


    def intra_cluster_variance(self, X, labels):
        
        total_variance = 0

        for k in range(self.K):
            
            cluster_points = X[labels == k]
            centroid = self.centroids[k]
            
            variance = np.sum((cluster_points - centroid) ** 2)
            total_variance += variance

        return total_variance


################################################################################################

# Cluster Validation

# usgin scikitlearn

def get_min_dist_idx(x, centroids):
    return np.argmin([np.linalg.norm(x - c) for c in centroids])


def _get_comembership_matrix(X_valid, train_centroids):
    n_samples, m_features = X_valid.shape
    return np.array([[1 if 
                    get_min_dist_idx(X_valid[i], train_centroids) == get_min_dist_idx(X_valid[j], train_centroids)
                    else 0 
                    for j in range(n_samples)
                    ] 
                    for i in range(n_samples)])

def _get_prediction_strength(M, validate_labels, k):

    ps = np.zeros(k)

    for l in range(k):
        member_idxs = np.where(validate_labels == l)[0]
        size = len(member_idxs)

        if size < 2: 
            ps[l] = np.nan
        else:
            sub_m = M[np.ix_(member_idxs, member_idxs)]
            pair_sum = np.sum(sub_m) - np.trace(sub_m)
            ps[l] = pair_sum / (size * (size - 1)) 

    return np.nanmin(ps)

def validate_clusters(k, X_train, X_valid):

    ps = np.zeros(k)    

    for i in range(1,k):

        kmeans = km(n_clusters=i, random_state=40, n_init=10).fit(X_train)
        train_labels = np.copy(kmeans.labels_)
        train_centroids = np.copy(kmeans.cluster_centers_)

        kmeans.fit(X_valid)
        test_labels = np.copy(kmeans.labels_)
        test_centroids = np.copy(kmeans.cluster_centers_)

        M = _get_comembership_matrix(X_valid, train_centroids)
        ps[i  - 1] = _get_prediction_strength(M, test_labels, k)

        return ps




