import numpy as np
from matplotlib import pyplot as plt

def lin_reg(X, y):
    X_b = np.c_[np.ones((X.shape[0], 1)), X]
    return np.linalg.inv(X_b.T @ X_b) @ X_b.T @ y


X_2_1, y_2_1 = np.loadtxt('https://data.bialonski.de/ml/franchise-data.txt', delimiter=',', unpack=True)

theta = lin_reg(X_2_1.reshape(-1, 1), y_2_1)

X_plot = np.linspace(X_2_1.min(), X_2_1.max())
X_plot_b = np.c_[np.ones((X_plot.shape[0], 1)), X_plot]
y_plot = X_plot_b @ theta

plt.scatter(X_2_1, y_2_1, label="Training Data")
plt.plot(X_plot, y_plot, color="red", label="Linear Regression")
plt.xlabel("Number of Habitants in the City (×10,000)")
plt.ylabel("Profit per Fastfood Truck (×10,000 €)")
plt.legend()
plt.show()

print("Intercept (theta0):", theta[0])
print("Slope (theta1):", theta[1])
