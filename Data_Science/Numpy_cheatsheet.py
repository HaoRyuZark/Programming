import numpy as np

# 1. ARRAYS, FIELDS AND METHODS
arr1 = np.array([1, 2, 3])            # create array from list
arr2 = np.array([[1, 2], [3, 4]])     # 2D array

print("Array:", arr1)
print("Shape:", arr1.shape)
print("Data type:", arr1.dtype)
print("Number of dimensions:", arr1.ndim)
print("Size (total elements):", arr1.size)

# 2. MULTIDIMENSIONAL ARRAYS
arr3 = np.zeros((2, 3))               # 2x3 matrix of zeros
arr4 = np.ones((3, 2))                # 3x2 matrix of ones
arr5 = np.eye(3)                      # 3x3 identity matrix
arr6 = np.arange(0, 10, 2)            # array([0,2,4,6,8])
arr7 = np.linspace(0, 1, 5)           # 5 points between 0 and 1 inclusive

print("Zeros:\n", arr3)
print("Identity:\n", arr5)
print("Arange:", arr6)
print("Linspace:", arr7)

# 3. SLICING
# General form: arr[start:stop:step]
# - start: index to begin (default 0)
# - stop: index to end (exclusive)
# - step: increment between indices (default 1)

arr8 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print("Original:\n", arr8)
print("First row:", arr8[0])                     # row 0
print("Second column:", arr8[:, 1])              # all rows, col 1
print("Top-left 2x2 subarray:\n", arr8[:2, :2])  # rows 0-1, cols 0-1

# Examples with step
arr9 = np.arange(10)
print("Original:", arr9)
print("Every second element:", arr9[::2])        # step = 2
print("From index 2 to 8:", arr9[2:9])            # start=2, stop=9
print("Reversed array:", arr9[::-1])             # negative step

# 4. ARITHMETIC
arr10 = np.array([1, 2, 3])
arr11 = np.array([4, 5, 6])
print("Add:", arr10 + arr11)
print("Subtract:", arr11 - arr10)
print("Multiply:", arr10 * arr11)
print("Divide:", arr11 / arr10)
print("Dot product:", np.dot(arr10, arr11))

# 5. BROADCASTING
arr12 = np.array([1, 2, 3])
print("Broadcast add scalar:", arr12 + 5)
print("Broadcast multiply scalar:", arr12 * 2)

matrix = np.ones((3, 3))
vec = np.array([1, 2, 3])
print("Matrix + Vector broadcasting:\n", matrix + vec)

# 6. AGGREGATE FUNCTIONS
arr13 = np.array([[1, 2, 3], [4, 5, 6]])
print("Sum:", arr13.sum())
print("Column-wise sum:", arr13.sum(axis=0))
print("Row-wise sum:", arr13.sum(axis=1))
print("Mean:", arr13.mean())
print("Max:", arr13.max())
print("Min:", arr13.min())

# 7. FILTERING
arr14 = np.arange(10)
print("Original:", arr14)
print("Even numbers:", arr14[arr14 % 2 == 0])
print("Greater than 5:", arr14[arr14 > 5])

# 8. RANDOM NUMBERS
rand1 = np.random.rand(3)             # uniform [0,1)
rand2 = np.random.randn(3)            # normal distribution
rand3 = np.random.randint(0, 10, 5)   # random integers between 0 and 9

print("Random uniform:", rand1)
print("Random normal:", rand2)
print("Random integers:", rand3)

# Reproducibility
np.random.seed(42)
print("Random with seed:", np.random.rand(3))

# 9. LINEAR ALGEBRA / MATH FUNCTIONS
mat = np.array([[1, 2], [3, 4]])


# Determinant
det = np.linalg.det(mat)
print("Determinant:", det)


# Inverse
inv = np.linalg.inv(mat)
print("Inverse:\n", inv)


# Eigenvalues and Eigenvectors
eigvals, eigvecs = np.linalg.eig(mat)
print("Eigenvalues:", eigvals)
print("Eigenvectors:\n", eigvecs)


# Diagonalization (if possible)
# A = P D P^-1 where D is diagonal with eigenvalues, P is matrix of eigenvectors
if np.linalg.matrix_rank(eigvecs) == mat.shape[0]:
    D = np.diag(eigvals)
    P = eigvecs
    P_inv = np.linalg.inv(P)
    reconstructed = P @ D @ P_inv
    print("Diagonal matrix D:\n", D)
    print("Reconstructed matrix from diagonalization:\n", reconstructed)


# Matrix multiplication
mat2 = np.array([[5, 6], [7, 8]])
print("Matrix multiplication:\n", np.dot(mat, mat2))


# Norms
print("Frobenius norm:", np.linalg.norm(mat))


# Solve linear system Ax = b
A = np.array([[3, 1], [1, 2]])
b = np.array([9, 8])
x = np.linalg.solve(A, b)
print("Solution of Ax=b:", x)


# Statistic

# 1. BASIC DESCRIPTIVE STATISTICS
arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])


print("Mean:", np.mean(arr))
print("Median:", np.median(arr))
print("Variance:", np.var(arr))
print("Standard Deviation:", np.std(arr))
print("Min:", np.min(arr))
print("Max:", np.max(arr))
print("Range:", np.ptp(arr)) # max - min


# 2. PERCENTILES & QUANTILES
print("25th percentile:", np.percentile(arr, 25))
print("50th percentile (median):", np.percentile(arr, 50))
print("75th percentile:", np.percentile(arr, 75))
print("Quantiles (0, 0.25, 0.5, 0.75, 1):", np.quantile(arr, [0, 0.25, 0.5, 0.75, 1]))


# 3. CORRELATION & COVARIANCE
x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])


print("Covariance matrix:\n", np.cov(x, y))
print("Correlation matrix:\n", np.corrcoef(x, y))


# 4. STANDARDIZATION & Z-SCORES
z_scores = (arr - np.mean(arr)) / np.std(arr)
print("Z-scores:", z_scores)


# 5. RANDOM SAMPLING FOR STATISTICS
np.random.seed(42)
rand_sample = np.random.choice(arr, size=5, replace=False)
print("Random sample (no replacement):", rand_sample)


rand_sample_repl = np.random.choice(arr, size=5, replace=True)
print("Random sample (with replacement):", rand_sample_repl)


# Example of bootstrap sampling (resampling with replacement)
bootstrap_sample = np.random.choice(arr, size=len(arr), replace=True)
print("Bootstrap sample:", bootstrap_sample)

# Reorganizing Arrays 

# 1. RESHAPE & FLATTEN
arr = np.arange(12)
print("Original:", arr)


reshaped = arr.reshape(3, 4)
print("Reshaped (3x4):\n", reshaped)


flattened = reshaped.flatten()
print("Flattened:", flattened)


raveled = reshaped.ravel() # similar to flatten but returns a view if possible
print("Raveled:", raveled)


# 2. TRANSPOSE & SWAP AXES
mat = np.array([[1, 2, 3], [4, 5, 6]])
print("Original matrix:\n", mat)
print("Transpose:\n", mat.T)


arr3d = np.arange(24).reshape(2, 3, 4)
print("Original 3D shape:", arr3d.shape)
print("Swap axes (0 and 2):", arr3d.swapaxes(0, 2).shape)


# 3. CONCATENATION & STACKING
a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6]])


concat = np.concatenate((a, b), axis=0)
print("Concatenated along rows:\n", concat)


stacked_v = np.vstack((a, b))
print("Stacked vertically:\n", stacked_v)


stacked_h = np.hstack((a, np.array([[7], [8]])))
print("Stacked horizontally:\n", stacked_h)


stacked_d = np.dstack((a, a))
print("Stacked depth-wise:\n", stacked_d)


# 4. SPLITTING ARRAYS
arr_split = np.arange(9).reshape(3, 3)
print("Original array:\n", arr_split)


split_rows = np.vsplit(arr_split, 3)
print("Split into rows:", split_rows)


split_cols = np.hsplit(arr_split, 3)
print("Split into cols:", split_cols)


# 5. REPEATING & TILING
arr2 = np.array([1, 2, 3])
print("Repeat elements:", np.repeat(arr2, 2))
print("Tile array:", np.tile(arr2, 3))

# Miscellaneous 

# 1. BOOLEAN INDEXING
arr = np.array([1, 2, 3, 4, 5, 6])


# Example: select elements greater than 3
bool_idx = arr > 3
print("Boolean index:", bool_idx)
print("Elements > 3:", arr[bool_idx])


# More compact
print("Elements > 3 (compact):", arr[arr > 3])


# 2. GET DATA FROM FILE
# Assume a CSV file named 'data.csv' with numeric data
# Example content:
# 1,2,3
# 4,5,6
# 7,8,9


# data = np.loadtxt('data.csv', delimiter=',') # uncomment when file exists
# print("Data from file:\n", data)


# Using genfromtxt for missing values
# data = np.genfromtxt('data.csv', delimiter=',', filling_values=0)


# 3. ADVANCED INDEXING
arr2d = np.array([[10, 20, 30], [40, 50, 60], [70, 80, 90]])


# Index specific rows and columns
rows = np.array([0, 1, 2])
cols = np.array([2, 1, 0])
print("Advanced indexing result:", arr2d[rows, cols]) # [30, 50, 70]


# Using integer array indexing
print("Select multiple elements:\n", arr2d[[0,2],[1,2]]) # elements at (0,1) and (2,2)


# Boolean array with shape matching
bool_arr = np.array([[True, False, True],[False, True, False],[True, False, True]])
print("Elements selected by boolean array:", arr2d[bool_arr])
