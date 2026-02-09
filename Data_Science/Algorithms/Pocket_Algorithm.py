import numpy as np
from matplotlib import pyplot as plt

def generate_points(N):
    return np.random.rand(N, 2)

def generate_decision_line():
    g = generate_points(2)
    # Properly extract x and y
    x1, y1 = g[0]
    x2, y2 = g[1]
    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1

    def getY(x):
        return m * x + b

    return getY

def getClassedPoints(N):
    np.random.seed(5)
    f = generate_decision_line()
    X = generate_points(N)
    y = np.array([1 if f(x[0]) > x[1] else -1 for x in X])
    # Introduce 10% label noise
    for i in np.random.randint(0, len(y), int(len(y) / 10)):
        y[i] = -y[i]
    return X, y, f

X_2_2, y_2_2, f = getClassedPoints(50)

def in_sample_error(X, y, w):
    predictions = np.sign(X @ w)
    misclassified = np.sum(predictions != y)
    return misclassified / len(y)

def pocket(X, y, T=1000):
    X_with_bias = np.column_stack((np.ones(X.shape[0]), X))
    
    w = np.zeros(X_with_bias.shape[1])
    w_best = np.copy(w)
    best_error = in_sample_error(X_with_bias, y, w_best)
    
    for _ in range(T):
        
        predictions = np.sign(X_with_bias @ w)
        misclassified_idx = np.where(predictions != y)[0]
        
        if len(misclassified_idx) == 0:
            break
        
        i = np.random.choice(misclassified_idx)
        w = w + y[i] * X_with_bias[i]
        
        current_error = in_sample_error(X_with_bias, y, w)
        
        if current_error < best_error:
            w_best = np.copy(w)
            best_error = current_error
    
    return w_best

w = pocket(X_2_2, y_2_2, T=1000)
print("Best weights:", w)
print("Final in-sample error:", in_sample_error(np.column_stack((np.ones(X_2_2.shape[0]), X_2_2)), y_2_2, w))

X_with_bias = np.column_stack((np.ones(X_2_2.shape[0]), X_2_2))
predictions = np.sign(X_with_bias @ w)

# Plot the data points with predictions
plt.figure(figsize=(10, 6))
plt.scatter(X_2_2[:, 0], X_2_2[:, 1], c=predictions, cmap='coolwarm', edgecolors='black')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.title('Pocket Algorithm Classification Results')

x_min, x_max = X_2_2[:, 0].min() - 0.1, X_2_2[:, 0].max() + 0.1
x_line = np.array([x_min, x_max])
y_line = -(w[0] + w[1] * x_line) / w[2]
plt.plot(x_line, y_line, 'g-', linewidth=2, label='Decision Boundary')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()
