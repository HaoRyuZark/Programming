import numpy as np
import matplotlib.pyplot as plt

class KMeans:

    def __init__(self, K=5, n_iters=100, plot_steps=False):        
        self.K = K
        self.n_iters = n_iters
        self.plot_steps = plot_steps
        self.clusters = [[] for _ in range(self.K)] # list of list of indices for each cluster
        self.centroids = [] 

    def predict(self, X):

        self.X = X
        self.n_samples, self.n_features = self.X.shape

        # Choose some random indices in form our samples
        random_samples_indx = np.random.choice(self.n_samples, self.K, replace=False)

        # Choose the current data point as the centroid
        self.centroids = [self.X[idx] for idx in random_samples_indx]

        # Iterative process
        for _ in range(self.n_iters):

            # assign samples to the centroids 
            self.clusters = self.create_clusters(self.centroids)

            if self.plot_steps:
                self.plot()

            # Update centroids
            centroids_old = self.centroids
            self.centroids = self._get_centroids(self.clusters)

            if self._is_converged(centroids_old, self.centroids):
                break 
            
            if self.plot_steps:
                self.plot()


        return self._get_clusters_labels(self.clusters)

    def create_clusters(self, centroids):
        clusters = [[] for _ in range(self.K)]

        for idx, sample in enumerate(self.X):
            centroid_idx = self._closest_centroid(self.centroids, sample)
            clusters[centroid_idx].append(idx)
        
        return clusters

    def _closest_centroid(self, centroids, sample):
        dists = [self._distance(sample, c) for c in centroids]
        return np.argmin(dists)

    def _distance(self, x,y):
        return np.linalg.norm(x - y)

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
        return np.equal(centroids_old, centroids_new)
 
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
