import numpy as np
import math
import pandas as pd
from matplotlib import pyplot as plt
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

#################################################################################################################################

# Helper Distance 
def get_euclidean_dist(x,y):    
    res = 0 
    for i in range(len(x)):
        res += pow(x[i] - y[i], 2)
    
    return math.sqrt(res)


#################################################################################################################################

# Import data
column_names = ['Class label', 'Alcohol', 'Malic acid', 'Ash', 'Alcalinity of ash', 'Magnesium', 'Total phenols', 'Flavanoids', 
                'Nonflavanoid phenols', 'Proanthocyanins', 'Color intensity', 'Hue', 'OD280/OD315 of diluted wines', 'Proline']
df = pd.read_csv('https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data', header=None)
df.columns = column_names

#################################################################################################################################

# Standardize function and data
def print_mean_and_std():
    for name in column_names:
        print("----------------" + name + "----------------")
        print(df[name].mean())
        print(df[name].std())

# Standardize data
X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values

X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.4, random_state=10)

train_mean = np.array(X_train).mean(axis=0)
train_std = np.array(X_train).std(axis=0)

# Z scoring directly
X_train = (X_train - train_mean) / train_std
X_test = (X_test - train_mean) / train_std  # Use training stats!

#################################################################################################################################

# NN implementation
def get_nearest_neighboor(x, X_train):
    distances = [get_euclidean_dist(x, xi) for xi in X_train]
    return distances.index(min(distances))

def NN(X_train, X_test, y_train):

    y_pred = []

    for x in X_test:
        nn_index = get_nearest_neighboor(x, X_train)
        y_pred.append(y_train[nn_index])

    return y_pred

y_pred = NN(X_train, X_test, y_train)

# Accuracy function
def accuracy(y_pred, y_test): 
    r = 0
    for i in range(0, len(y_pred)):
        if y_pred[i] == y_test[i]:
            r += 1
    
    return r / len(y_test)

acc = accuracy(y_pred, y_test)

#################################################################################################################################

# Getting PCs via Eigenstuff 

cov = (X.T @ X) / (X.shape[0] - 1)

eigenvals, eigenvecs = np.linalg.eig(cov)

indxsorted = np.argsort(eigenvals)

s_eigvecs = np.array([eigenvecs[indxsorted[i]] for i in range(0, len(indxsorted))])
s_eigvals = np.array([eigenvals[indxsorted[i]] for i in range(0, len(indxsorted))])


#################################################################################################################################

# PVE

var_total = s_eigvals.sum()

pve = np.array([s_eigvals[i] / var_total for i in range(0, len(eigenvals))])

plt.scatter(s_eigvals, pve, marker="o")
plt.xlabel("Eigenvalues")
plt.ylabel("PVE")
plt.show()

#################################################################################################################################

# PCA reduction 

n_components = 3

# Getting components
pca_components = s_eigvecs[-n_components:].T

# Projectin training data
X_train_pca = X_train @ pca_components

# Erstellen der einzelnen PCA-Komponenten für die Visualisierung
x1 = X_train_pca[:, 0]
x2 = X_train_pca[:, 1]
x3 = X_train_pca[:, 2]

#################################################################################################################################

# Visualization

# 2D visualization
plt.figure(figsize=(10, 6))
plt.scatter(x1, x2, c=y_train, cmap='viridis', edgecolors='k', s=50, alpha=0.7)
plt.xlabel('Erste PCA-Komponente (PC1)')
plt.ylabel('Zweite PCA-Komponente (PC2)')
plt.title('Wein-Datensatz im PCA-Raum')
plt.colorbar(label='Weinklasse')
plt.grid(True, alpha=0.3)
plt.show()

# 3D visualization
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
scatter = ax.scatter(x1, x2, x3, c=y_train, cmap='viridis', s=50, alpha=0.7, edgecolors='k')
ax.set_xlabel('PC1')
ax.set_ylabel('PC2')
ax.set_zlabel('PC3')
ax.set_title('Wein-Datensatz im 3D PCA-Raum')
plt.colorbar(scatter, label='Weinklasse')
plt.show()



