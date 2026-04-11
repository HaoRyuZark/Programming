# NumPy 

## Import 

```python 
import numpy as np
```

--- 

## Array & Matrices Initialization

Basic Initialization techinques: 

- `np.array()`:

```python 
arr1 = np.array([1, 2, 3])            # create array from list
arr2 = np.array([[1, 2], [3, 4]])     # 2D array
ele = arr2[0,0]                       #accesing element at [0][0]
```

--- 

## Indexing

```python 
arr2d = np.array([[10, 20, 30], [40, 50, 60], [70, 80, 90]])

# Index specific rows and columns
rows = np.array([0, 1, 2])
cols = np.array([2, 1, 0])
print("Advanced indexing result:", arr2d[rows, cols]) # [30, 50, 70]

# Using integer array indexing
print("Select multiple elements:\n", arr2d[[0,2],[1,2]]) # elements at (0,1) and (2,2)
```

--- 

## View & Copy 

- `view()`:

- `copy()`:

```python 
original = np.array([1, 2, 3, 4, 5])

view = original.view()

copy = original.copy()
copy = np.copy(original)

view[0] = 99
copy[1] = 88

print("Original array:", original)
print("View after modification:", view)
print("Copy after modification:", copy)


```
--- 

## Identity Matrix

- `np.eye()`:

```python 
arr5 = np.eye(3)                      # 3x3 identity matrix
```

--- 

## Points in a Range 

- `np.linspace()`:

```python 
arr7 = np.linspace(0, 1, 5)           # 5 points between 0 and 1 inclusive
```

--- 

## Ones and Zeroes 

- `np.zeros()`

- `np.ones()`

```python 
arr3 = np.zeros((2, 3))               # 2x3 matrix of zeros
arr4 = np.ones((3, 2))                # 3x2 matrix of ones
```

--- 

## Points in a range in a logarithmic scale 

- `np.logspace()`: 

```python 
arr8 = np.logspace(-9, 3, num=13)     # array with numbers evely spaces on a logarithmic scale
```

--- 

## Accessing Attributes 

- `shape`:
- `dtype`:
- `ndim`:
- `size`:

```python 
print("Array:", arr)
print("Shape:", arr.shape)
print("Data type:", arr.dtype)
print("Number of dimensions:", arr.ndim)
print("Size (total elements):", arr.size)
```

--- 

## Axis 

**Axis** is a common parameter of different numpy and pandas features. It is used to 
define the axis a function should act onto. For example for a 2d array we have 2 dimension 0 and 1. 

```python

# 3 by 3 matrix with three rows with [1,2,3]
axis_example = np.array([np.arange(3) for _ in range(3)]) 

# axis=0: rows
# axis=1: cols 

# Mean vector 
m = np.mean(axis_example, axis=1)

# Sum of the rows
m = np.mean(axis_example, axis=0)

# Axis  Axis -> (1)
#   |   1   3   4
#   "   1   1   1 
#  (0)  0   2   4
```

### Example: Axises for 4D array

- **axis = 0**: act on the 3d arrays.
- **axis = 1**: act on the 2d arrays in each 3d array.
- **axis = 2**: act on the rows in each 2d array.
- **axis = 3**: act on the col in each 2d array.

--- 

## Sorting 

- `np.sort()`:

```python 
unsorted = np.array([3, 1, 4, 1, 5, 9, 2])
sorted_arr = np.sort(unsorted)
print("Unsorted:", unsorted)
print("Sorted:", sorted_arr)
```

--- 

## Sorting Indexes

- `np.argsort()`:

```python 
sort_indices = np.argsort(unsorted)
print("Sort indices:", sort_indices)
print("Sorted using indices:", unsorted[sort_indices])
```

--- 

## Random numbers

- `np.random.default_rng()`:

- `np.random.randint()`:

- `np.random.randn()`:

- `np.random.rand()`:

- `choice()`:

```python 
rng = np.random.default_rng()           # way to create random generator
mat = np.random.randint(0, 50, (3, 3))  # 3x3 matrix with random integers between 0 and 49

rand1 = np.random.rand(3)             # uniform [0,1)
rand2 = np.random.randn(3)            # normal distribution
rand3 = np.random.randint(0, 10, 5)   # random integers between 0 and 9

print("Random uniform:", rand1)
print("Random normal:", rand2)
print("Random integers:", rand3)
print("Choice", rng.choice(arr4, size=(3,3))) # the size allows us to choose the dimentsions of the choise in this case 3 by 3 array 
```

--- 

## Reshape & Flatten 

- `np.arange()`:

- `np.reshape()`:

- `flatten()`:

- `ravel()`:

```python 
arr = np.arange(12)
print("Original:", arr)

reshaped = arr.reshape(3, 4)         # the reshape only works if the total number of elements matchs
print("Reshaped (3x4):\n", reshaped)

reshaped = arr.reshape(2, 3, 4)     # in this case we repeat the process two times given us the old output of an array -> [reshaped, reshaped]
print("Reshaped again:\n", reshaped)

flattened = reshaped.flatten()
print("Flattened:", flattened)

raveled = reshaped.ravel() # similar to flatten but returns a view if possible
print("Raveled:", raveled)

col_vec = np.arange(12).reshape(-1, 1) # when passing -1 numpy figures out the other dimension
col_vec = np.arange(12).reshape(12, 1) # same result as above
print("Column vector:", col_vec)
```

--- 

## Transpose & Swap Axes

- `.T`:

- `swapaxes()`:

```python 
mat = np.array([[1, 2, 3], [4, 5, 6]])
print("Original matrix:\n", mat)
print("Transpose:\n", mat.T)

arr3d = np.arange(24).reshape(2, 3, 4)
print("Original 3D shape:", arr3d.shape)
print("Swap axes (0 and 2):", arr3d.swapaxes(0, 2).shape)
```

--- 

## Concatenation & Stacking 

- `np.concatenate()`:

- `np.vstack()`:

- `np.hstack()`:

- `np.dstack()`:

- `np.column_stack()`:

```python 
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

column_stack = np.column_stack((a, b))
print("Stacked side by side:\n", stacked_d)
```

--- 

## Blocks 

Numpy blocks allows us to construct matrices using other matrices as lego blocks 
The only criteria is that the dimenions match together.

- `np.block()`:

```python 
b = np.block([[np.eye(2) * 2, np.zeros((2,3))], [np.ones((3,2)), np.eye(3) * 3]])
```

--- 

## Slicing 

General form: `arr[start:stop:step, ..]` we can apply this to all dimensions becuase of the access via arr[idx_dim1, idx_dim2, ..]

- `start`: index to begin (default 0)
- `stop`: index to end (exclusive)
- `step`: increment between indices (default 1)

```python 
arr8 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print("Original:\n", arr8)
print("First row:", arr8[0])                     # row 0
print("Second column:", arr8[:, 1])              # all rows, col 1
print("Top-left 2x2 subarray:\n", arr8[:2, :2])  # rows 0-1, cols 0-1
print("Select column 0", arr2[:, 0])
print("Selection only all cols except the first\n", arr[0:, 1:] )

# Examples with step
arr9 = np.arange(10)

print("Original:", arr9)
print("Every second element:", arr9[::2])        # step = 2
print("From index 2 to 8:", arr9[2:9])            # start=2, stop=9
print("Reversed array:", arr9[::-1])             # negative step
```

--- 

## Arithmetic

```python 
arr10 = np.array([1, 2, 3])
arr11 = np.array([4, 5, 6])

print("Scalar multiplication:", arr10 * 2)
print("Scalar addition:", arr10 + 2)

print("Add:", arr10 + arr11)
print("Subtract:", arr11 - arr10)
print("Multiply:", arr10 * arr11)
print("Power:", arr10 ** arr11)
print("Divide:", arr11 / arr10)
print("Dot product:", np.dot(arr10, arr11))
print("Root:", np.sqrt(arr10))
print("Rounding:", np.round(arr11))
```

## Dot 

- `np.dot()`:

--- 

## Outher 

- `np.outher()`:

--- 

## Matrix Multiplication 

- `@`:

```python 

```

--- 

## Boolean Array 

```python 
scores = np.array([i for i in range(1,101)])
print(scores <= 50) # prints a boolen array 
```

--- 

## Broadcasting

This allows NumPy to perform operations on arrays with different shapes by virtually expanding dimensions 
so they mathc the larger array's shape. 

For this to work the dimensions should mathc or one of them has to 1. 

- Works: (4,4) (4,1) at least one dimension matches or is 1.

- Fails: (2,4) (3, 5) no dimensions match.


```python 
arr12 = np.array([1, 2, 3])

print("Broadcast add scalar:", arr12 + 5)
print("Broadcast multiply scalar:", arr12 * 2)

matrix = np.ones((3, 3))
vec = np.array([1, 2, 3])
print("Matrix + Vector broadcasting:\n", matrix + vec)
```

--- 

## Aggreate Functions 

- `sum()`:

- `mean()`:

- `max()`:

- `min`:

```python
arr13 = np.array([[1, 2, 3], [4, 5, 6]])
print("Sum:", arr13.sum())
print("Column-wise sum:", arr13.sum(axis=0))
print("Row-wise sum:", arr13.sum(axis=1))
print("Mean:", arr13.mean())
print("Max:", arr13.max())
print("Min:", arr13.min())
```

--- 

## Filtering 

Numpy provides different version for getting different views of our arrays. 

- **Boolean Indexing**:

- **Boolean Condition**:

- `np.where()`:

```python 
arr14 = np.arange(10)

print("Original:", arr14)
print("Array of booleans, based on a boolean condition (greater than 5):", arr14 > 5)
print("Even numbers:", arr14[arr14 % 2 == 0])
print("Greater than 5:", arr14[arr14 > 5])
print("Array with elements which obey the condition:", np.where(arr14 > 1, arr14, 0))
```

--- 

## Linear Algebra 

- `np.linalg.det()`:

- `np.linalg.inv()`:

- `np.linalg.eig()`:

- `np.linalg.matrix_rank()`:

- `np.linalg.norm()`:

- `np.linalg.solve()`:

```python 
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


# Solve linear systems Ax = b

A = np.array([[3, 1], [1, 2]])
b = np.array([9, 8])
x = np.linalg.solve(A, b)
print("Solution of Ax=b:", x)
```

--- 

## Statistical Functions 

- `np.mean()`:

- `np.median()`:

- `np.var()`:

- `np.std()`:

- `np.min()`:

- `np.max()`:

- `np.ptp()`:

- `np.percentile()`:

- `np.quantile()`:

```python 
arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])

print("Mean:", np.mean(arr))
print("Median:", np.median(arr))
print("Variance:", np.var(arr))
print("Standard Deviation:", np.std(arr))
print("Min:", np.min(arr))
print("Max:", np.max(arr))
print("Range:", np.ptp(arr)) # max - min

print("25th percentile:", np.percentile(arr, 25))
print("50th percentile (median):", np.percentile(arr, 50))
print("75th percentile:", np.percentile(arr, 75))
print("Quantiles (0,25,5,75, 1):", np.quantile(arr, [0,25,5,75, 1]))
```

--- 

## Covariance and Correlation 

- `np.cov()`:

- `np.corrcoef()`:

```python
x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])

print("Covariance matrix:\n", np.cov(x, y))
print("Correlation matrix:\n", np.corrcoef(x, y))
```

--- 

## Standardization & Z-scores

```python
z_scores = (arr - np.mean(arr)) / np.std(arr)
print("Z-scores:", z_scores)
```

--- 

## Random Sampling 

```python 
np.random.seed(42)
rand_sample = np.random.choice(arr, size=5, replace=False)
print("Random sample (no replacement):", rand_sample)

rand_sample_repl = np.random.choice(arr, size=5, replace=True)
print("Random sample (with replacement):", rand_sample_repl)

# Example of bootstrap sampling (resampling with replacement)
bootstrap_sample = np.random.choice(arr, size=len(arr), replace=True)
print("Bootstrap sample:", bootstrap_sample)
```

--- 

## Splitting 

- `np.vsplit()`:

- `np.hsplit()`:

- `np.repeat()`:

- `np.tile()`:

```python 
arr_split = np.arange(9).reshape(3, 3)
print("Original array:\n", arr_split)

split_rows = np.vsplit(arr_split, 3)
print("Split into rows:", split_rows)

split_cols = np.hsplit(arr_split, 3)
print("Split into cols:", split_cols)

arr2 = np.array([1, 2, 3])
print("Repeat elements:", np.repeat(arr2, 2))
print("Tile array:", np.tile(arr2, 3))
```

--- 

## Input 

- `np.loadtxt()`:

- `np.loadcsv()`:

- `np.genfromtxt()`:

- add More

```python 
data = np.loadtxt('data.csv', delimiter=',') # uncomment when file exists
print("Data from file:\n", data)

# Using genfromtxt for missing values
data = np.genfromtxt('data.csv', delimiter=',', filling_values=0)
```

--- 

## Vectorized operations

A lot of opertions in numpy can act on whole vectors instead of single elements. This can improve performance by avoiding loops 

- `np.vectorize()`:

```python 
def is_even(x):
    return 1 if x % 2 == 0 else 0

vectorized_is_even = np.vectorize(is_even) # now this new function can act on vector, optimizing performance
```

--- 

## Custom Datatypes 

```python 
dt = np.dtype(np.int32) # used for declearing datatypes as dictionaries
```
