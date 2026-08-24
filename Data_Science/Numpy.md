# NumPy

## Import

```python
import numpy as np
```

---

## NumPy Array Object

This is the main object on which most operations are performed.
The dimensions are called axes, with 0 for rows, 1 for columns, 2 for depth, etc.

### Attributes of the NumPy Array

- `ndarray.ndim`: number of dimensions.

- `ndarray.shape`: tuple describing the array dimensions.

- `ndarray.size`: total number of elements in the array.

- `ndarray.dtype`: object with information about the data type.

- `ndarray.itemsize`: size in bytes of each element.

- `ndarray.data`: address of the buffer containing the actual elements.

```python
import numpy as np
data: np.ndarray = np.array([[1, 2, 3] for _ in range(3)])

print(data)
print(f"Dimensions: {data.ndim}")    # 2
print(f"Shape: {data.shape}")        # (3, 3)
print(f"Size: {data.size}")          # 9
print(f"dtype: {data.dtype}")        # int64
print(f"itemsize: {data.itemsize}")  # 8
print(f"data: {data.data}")
```

### Axis

**Axis** is a common parameter in different NumPy and pandas functions. It defines which axis a function should act on. For a 2D array we have 2 dimensions: 0 and 1.

#### 2D Array Example

- `axis=0`: acts along rows (reduces rows, producing one result per column).
- `axis=1`: acts along columns (reduces columns, producing one result per row).

```python
# 3x3 matrix where each row is [0, 1, 2]
axis_example = np.array([np.arange(3) for _ in range(3)])

# Mean across rows → one value per column
m0 = np.mean(axis_example, axis=0)  # [0. 1. 2.]

# Mean across columns → one value per row
m1 = np.mean(axis_example, axis=1)  # [1. 1. 1.]
```

#### Example: Axes for a 4D Array

- **axis = 0**: acts on the 3D arrays.
- **axis = 1**: acts on the 2D arrays inside each 3D array.
- **axis = 2**: acts on the rows inside each 2D array.
- **axis = 3**: acts on the columns inside each 2D array.

---

## Array & Matrix Initialization

### Basic Initialization

- `np.array(object, dtype=None, ndmin=0)`: creates an ndarray from a Python sequence.
  - `object`: a list, tuple, or nested sequence.
  - `dtype`: desired data type (e.g., `np.float64`, `np.int32`). Inferred if not specified.
  - `ndmin`: minimum number of dimensions the result must have.

```python
arr1 = np.array([1, 2, 3])               # 1D array
arr2 = np.array([[1, 2], [3, 4]])         # 2D array

ele = arr2[0, 0]                          # 1 — element at row 0, col 0

arr_min2d = np.array([1, 2, 3], ndmin=2) # shape (1, 3) instead of (3,)
```

### Array Creation with a Specified Data Type

```python
floating_zeros = np.zeros((4, 4), dtype=np.float64)  # 4x4 matrix of float64 zeros
rang = np.arange(0, 100, 2, dtype=np.int8)            # even numbers 0..98 as int8
```

### Other Types of Array Creation

- `np.arange(start=0, stop, step=1, dtype=None)`: similar to Python's `range()` but returns an ndarray.
  - `start`: start of the interval (inclusive, default 0).
  - `stop`: end of the interval (exclusive).
  - `step`: spacing between values (default 1).
  - `dtype`: data type of the output array.

- `np.linspace(start, stop, num=50, endpoint=True, dtype=None)`: returns evenly spaced numbers over a specified interval.
  - `start`: start of the sequence.
  - `stop`: end of the sequence.
  - `num`: number of evenly spaced samples (default 50).
  - `endpoint`: if `True`, `stop` is the last sample (default `True`).

- `np.logspace(start, stop, num=50, base=10.0, dtype=None)`: returns numbers evenly spaced on a logarithmic scale.
  - `start`: exponent for the start value (`base ** start`).
  - `stop`: exponent for the stop value (`base ** stop`).
  - `num`: number of samples (default 50).
  - `base`: base of the logarithmic scale (default 10).

- `np.ones(shape, dtype=float)`: returns a new array filled with ones.
  - `shape`: int or tuple of ints defining the shape.
  - `dtype`: data type (default `float`).

- `np.zeros(shape, dtype=float)`: returns a new array filled with zeros.
  - `shape`: int or tuple of ints defining the shape.
  - `dtype`: data type (default `float`).

- `np.eye(N, M=None, k=0, dtype=float)`: returns a 2D identity-like matrix.
  - `N`: number of rows.
  - `M`: number of columns (default equals `N`).
  - `k`: index of the diagonal (0 = main, positive = above, negative = below).

- `np.empty(shape, dtype=float)`: returns an uninitialized array of a given shape. Values are whatever happens to be in memory — use with care.
  - `shape`: int or tuple of ints.
  - `dtype`: data type (default `float`).

- `np.full(shape, fill_value, dtype=None)`: returns a new array filled with a given value.
  - `shape`: int or tuple of ints.
  - `fill_value`: scalar value to fill the array with.

```python
arr3 = np.zeros((2, 3))               # 2x3 matrix of zeros
arr4 = np.ones((3, 2))                # 3x2 matrix of ones
arr5 = np.eye(3)                      # 3x3 identity matrix
arr6 = np.eye(3, k=1)                 # identity with diagonal shifted one above the main
arr7 = np.linspace(0, 1, 5)           # [0.0, 0.25, 0.5, 0.75, 1.0]
arr8 = np.logspace(-9, 3, num=13)     # 13 values from 1e-9 to 1e3 on a log scale
arr9 = np.full(5, 7)                  # [7, 7, 7, 7, 7]
arr10 = np.arange(0, 10, 2)           # [0, 2, 4, 6, 8]
arr11 = np.empty((2, 2))              # uninitialized 2x2 array
```

---

## View & Copy

Sometimes when working with arrays, the data is copied and sometimes it is not, depending on the type of operation.
Assigning an array to another variable creates just a **view** — an object pointing to the same data (a **shallow copy**).
Changes to the view affect the original.

To create a **deep copy**, use `copy()` to fully replicate the array.

- `arr.view(dtype=None)`: returns a new array that looks at the same data.
  - `dtype`: if provided, the new array interprets the same memory with a different data type.

- `arr.copy(order='C')`: returns a full deep copy of the array.
  - `order`: memory layout — `'C'` (row-major) or `'F'` (column-major).

- `arr.base`: attribute used to check if an array is a view or a copy. Returns `None` if it is not a view, or the base array if it is.

```python
original = np.array([1, 2, 3, 4, 5])

view = original.view()
copy = original.copy()   # also: np.copy(original)

view[0] = 99
copy[1] = 88

print("Original:", original)  # [99, 2, 3, 4, 5] — affected by the view change
print("View:", view)           # [99, 2, 3, 4, 5]
print("Copy:", copy)           # [1, 88, 3, 4, 5] — independent

print("view.base is original:", view.base is original)  # True
print("copy.base is None:", copy.base is None)          # True

a = np.array([[ 0,  1,  2,  3],
              [ 4,  5,  6,  7],
              [ 8,  9, 10, 11]])

c = a.reshape(2, 6)  # reshape returns a view when possible
c[0, 4] = 66666      # modifies a[1, 0] since they share memory
print("Original a after view change:\n", a)
```

### Operations That Create Views

- Reassigning an array to another variable.
- Reshaping.
- Basic (simple) indexing and slicing.

### Operations That Create Copies

- Advanced indexing (boolean or fancy indexing).
- Mathematical operations (produce new arrays).
- Normal array creation.

---

## Indexing

Each axis gets its own index using `[start:stop:step, start:stop:step, ...]`. This means we can
access elements with the notation `arr[i, j, k], arr[(i, j, k)]` instead of `arr[i][j][k]`, which also allows slicing.

```python
arr2d = np.array([[10, 20, 30], [40, 50, 60], [70, 80, 90]])

print(arr2d[(0,1)] == arr2d[0][1]) # equivalent
print(arr2d[0, 1])    # 20 — row 0, col 1
print(arr2d[-1, -1])  # 90 — last row, last col
```

### Advanced Indexing

Triggered when an array or list is used for indexing. Always returns a **copy**.

```python
arr2d = np.array([[10, 20, 30], [40, 50, 60], [70, 80, 90]])

# Pair up indices: selects (0,2), (1,1), (2,0)
rows = np.array([0, 1, 2])
cols = np.array([2, 1, 0])
print("Diagonal-like selection:", arr2d[rows, cols])  # [30, 50, 70]

# Select elements at (0,1) and (2,2)
print("Multiple elements:", arr2d[[0, 2], [1, 2]])    # [20, 90]
```

### ix_ 

- `np.ix_(*args)`: takes N 1D sequences and returns N outputs of dimension N such that 
the shape is 1 in al but one dimension. In other words it takes 1D index arrays and turn them into 
arrays that can be used to select the **Cartesian product** of those indices.

This can be used for indexing and array on very specific indices like for example sub-matrices. 

```python 
import numpy as np

a = np.arange(10).reshape(2, 5)

# 2 by 5
# array([[0, 1, 2, 3, 4],
#        [5, 6, 7, 8, 9]])

# we want to select the elements at in the rows 0, 1 and the column 2, 4
ixgrid = np.ix_([0, 1], [2, 4])

#(array([[0], [1]]), 
  array([[2, 4]]))

# ixgrid[0].shape, ixgrid[1].shape
# ((2, 1), (1, 2))

a[ixgrid]
# array([[2, 4],
#        [7, 9]])
```

---

## Slicing

General form: `arr[start:stop:step, start:stop:step, ...]` — applicable to all dimensions.

- `start`: index to begin (default 0).
- `stop`: index to end (exclusive).
- `step`: increment between indices (default 1); use -1 for reverse order.

```python
arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print("First row:", arr[0])                   # [1, 2, 3]
print("Second column:", arr[:, 1])            # [2, 5, 8]
print("Top-left 2x2:\n", arr[:2, :2])         # [[1,2],[4,5]]
print("All cols except first:\n", arr[:, 1:]) # [[2,3],[5,6],[8,9]]

# Step examples
arr9 = np.arange(10)
print("Every second element:", arr9[::2])     # [0, 2, 4, 6, 8]
print("From index 2 to 8:", arr9[2:9])        # [2, 3, 4, 5, 6, 7, 8]
print("Reversed:", arr9[::-1])                # [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
```

---

## Boolean Array

A boolean condition applied to an array returns an array of booleans of the same shape.

```python
scores = np.array([i for i in range(1, 101)])
mask = scores <= 50
print(mask)           # [True, True, ..., False, False]
print(scores[mask])   # [1, 2, ..., 50]
```

---

## Iterations

- `np.nditer(op, order='K', flags=None, op_flags=None)`: efficient multi-dimensional iterator over one or more arrays.
  - `op`: array or sequence of arrays to iterate over.
  - `order`: iteration order — `'C'` (row-major), `'F'` (column-major), `'A'` (Fortran if contiguous, else C), `'K'` (as close to memory layout as possible).
  - `flags`: list of iterator-level flags. Common values: `'multi_index'` (track the current N-D index), `'external_loop'` (return larger chunks instead of single elements for performance).
  - `op_flags`: per-operand flags — e.g., `['readwrite']` to modify the array in place, `['writeonly']` for output-only operands.

- `np.ndenumerate(arr)`: multi-dimensional equivalent of `enumerate()`. Yields `(index_tuple, value)` pairs for every element.
  - `arr`: input array.

- `np.ndindex(*shape)`: iterates over every index tuple for a virtual array with the given shape.
  - `*shape`: integers defining the shape.

- `np.apply_along_axis(func1d, axis, arr, *args, **kwargs)`: applies a 1D function to each 1D slice of an array along a given axis.
  - `func1d`: callable that takes a 1D array and returns a scalar or 1D array.
  - `axis`: axis along which `func1d` is applied.
  - `arr`: input array.
  - `*args`, `**kwargs`: extra arguments forwarded to `func1d`.

- `np.apply_over_axes(func, a, axes)`: applies a function repeatedly over multiple axes.
  - `func`: callable of the form `func(a, axis)` that reduces one axis at a time.
  - `a`: input array.
  - `axes`: list of axes over which to apply the function.

```python
arr = np.array([[1, 2, 3], [4, 5, 6]])

# Basic iteration (row-major by default)
for x in np.nditer(arr):
    print(x, end=" ")  # 1 2 3 4 5 6
print()

# Column-major order
for x in np.nditer(arr, order='F'):
    print(x, end=" ")  # 1 4 2 5 3 6
print()

# In-place modification with readwrite flag
arr_copy = arr.copy()
with np.nditer(arr_copy, op_flags=['readwrite']) as it:
    for x in it:
        x[...] = x * 2
print("Doubled:\n", arr_copy)  # [[2 4 6], [8 10 12]]

# Track multi-index
with np.nditer(arr, flags=['multi_index']) as it:
    while not it.finished:
        print(f"Index {it.multi_index}: {it[0]}")
        it.iternext()

# ndenumerate — (index_tuple, value) pairs
for idx, val in np.ndenumerate(arr):
    print(f"Index {idx}: {val}")
# Index (0, 0): 1
# Index (0, 1): 2  ...

# ndindex — iterate over all index tuples for a given shape
for idx in np.ndindex(2, 3):
    print(idx, end=" ")  # (0,0) (0,1) (0,2) (1,0) (1,1) (1,2)
print()

# Broadcast-iterate over two arrays
a = np.array([1, 2, 3])
b = np.array([[10], [20], [30]])
for x, y in np.nditer([a, b]):
    print(f"{int(x)}+{int(y)}", end="  ")  # 1+10  2+10  3+10  1+20 ...
print()

# apply_along_axis — normalize each row
data = np.array([[1.0, 2.0, 3.0], [4.0, 8.0, 12.0]])
normalized = np.apply_along_axis(
    lambda row: (row - row.mean()) / row.std(), axis=1, arr=data
)
print("Row-normalized:\n", normalized)

# apply_over_axes — sum over both axes 0 and 1 of a 3D array
arr3d = np.arange(24).reshape(2, 3, 4)
result = np.apply_over_axes(np.sum, arr3d, axes=[0, 1])
print("Sum over axes 0 & 1, shape:", result.shape)  # (1, 1, 4)
```

---

## Masking

A **mask** is a boolean array of the same shape as the data, where `True` marks values as invalid or missing. NumPy's `numpy.ma` module provides masked arrays that carry this mask alongside the data, so all operations silently ignore masked elements.

- `np.ma.array(data, mask=False, fill_value=None, dtype=None)`: creates a masked array.
  - `data`: input data array or sequence.
  - `mask`: boolean array — `True` marks a value as masked (invalid). A scalar `False` means no masking.
  - `fill_value`: value used to replace masked elements when exporting to a regular array.

- `np.ma.masked_where(condition, a, copy=True)`: masks elements of `a` where `condition` is `True`.
  - `condition`: boolean array with the same shape as `a`.
  - `a`: input array.

- `np.ma.masked_greater(a, value)` / `np.ma.masked_less(a, value)`: masks elements strictly greater than / less than `value`.

- `np.ma.masked_greater_equal(a, value)` / `np.ma.masked_less_equal(a, value)`: masks elements ≥ / ≤ `value`.

- `np.ma.masked_equal(a, value)`: masks elements equal to `value`. Useful for sentinel values like `-9999`.

- `np.ma.masked_outside(a, v1, v2)`: masks elements outside the interval `[v1, v2]`.

- `np.ma.masked_invalid(a)`: masks NaN and Inf values in `a`.
  - `a`: input array.

- `np.ma.filled(a, fill_value=None)`: returns a copy of `a` with masked values replaced by `fill_value`.
  - `a`: masked array.
  - `fill_value`: replacement scalar. Falls back to the array's own `fill_value` if `None`.

- `np.ma.compressed(a)`: returns a 1D array containing only the unmasked (valid) elements.
  - `a`: masked array.

- `np.ma.getmask(a)`: returns the mask of `a`, or `np.ma.nomask` (`False`) if the array is not masked.

- `np.ma.getdata(a)`: returns the underlying data array, ignoring the mask.

- `np.ma.count(a, axis=None)`: counts the non-masked elements along an axis.

```python
import numpy as np

data = np.array([1.0, -999.0, 3.0, -999.0, 5.0])

# Mask sentinel values
masked = np.ma.masked_equal(data, -999.0)
print("Masked array:", masked)          # [1.0 -- 3.0 -- 5.0]
print("Mask:", masked.mask)             # [False  True False  True False]

# Aggregate functions automatically skip masked values
print("Mean (valid only):", masked.mean())   # 3.0  (= (1+3+5)/3)
print("Sum:", masked.sum())                  # 9.0
print("Valid count:", np.ma.count(masked))   # 3

# Mask by condition
arr = np.array([4, 7, 2, 9, 1, 5])
masked2 = np.ma.masked_where(arr > 5, arr)
print("Masked (>5):", masked2)          # [4 -- 2 -- 1 5]

# Mask by range
masked3 = np.ma.masked_outside(arr, 2, 6)
print("Masked outside [2,6]:", masked3)  # [4 -- 2 -- -- 5]

# Mask NaN and Inf
arr_bad = np.array([1.0, np.nan, 3.0, np.inf, 5.0])
masked_inv = np.ma.masked_invalid(arr_bad)
print("Masked invalid:", masked_inv)    # [1.0 -- 3.0 -- 5.0]

# Fill masked values for export or plotting
filled = np.ma.filled(masked, fill_value=0.0)
print("Filled:", filled)               # [1. 0. 3. 0. 5.]

# Compressed: only the valid values as a flat 1D array
print("Compressed:", np.ma.compressed(masked))  # [1. 3. 5.]

# Manual mask
mask = np.array([False, True, False, True, False])
m = np.ma.array(data, mask=mask, fill_value=-1.0)
print("Custom masked array:", m)
print("Underlying data:", np.ma.getdata(m))  # [-999. ...] — mask ignored

# 2D masked array
mat = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
mmat = np.ma.masked_where(mat % 2 == 0, mat)  # mask even numbers
print("2D masked (even numbers hidden):\n", mmat)
print("Column means:", mmat.mean(axis=0))     # only odd values contribute
```

---

## Filtering

NumPy provides different ways to select elements from arrays.

- `arr[condition]`: **boolean indexing** — returns elements where `condition` is `True`.
  Example: `arr[arr[:, 1] > 18]` returns all rows where the second column is greater than 18.

- `np.where(condition, x, y)`: returns elements from `x` where `condition` is `True`, otherwise from `y`.
  - `condition`: boolean array or expression.
  - `x`: values to use where condition is `True`.
  - `y`: values to use where condition is `False`.

- `np.all(a, axis=None)`: returns `True` if all elements along the given axis evaluate to `True`.
  - `a`: input array.
  - `axis`: axis to reduce over. If `None`, checks all elements.

- `np.any(a, axis=None)`: returns `True` if any element along the given axis evaluates to `True`.
  - `a`: input array.
  - `axis`: axis to reduce over.

- `np.nonzero(a)`: returns the indices of the elements that are non-zero  
  - `a`: input array.

- `np.argwhere(a)`: Find the indices of array elements that are non-zero, grouped by element.
  - `a`: input array.


```python
arr = np.arange(10)

print("Boolean mask (> 5):", arr > 5)                        # [F F F F F F T T T T]
print("Even numbers:", arr[arr % 2 == 0])                    # [0 2 4 6 8]
print("Greater than 5:", arr[arr > 5])                       # [6 7 8 9]
print("where (>1 keep, else 0):", np.where(arr > 1, arr, 0)) # [0 0 2 3 4 5 6 7 8 9]
print("All > 0:", np.all(arr > 0))                           # False (0 is in arr)
print("Any > 8:", np.any(arr > 8))                           # True

x = np.array([[3, 0, 0], [0, 4, 0], [5, 6, 0]])
np.nonzero(x)                                                # [[0, 1, 2, 2], [0, 1, 0, 1]]
```

---

## Sorting

- `np.sort(a, axis=-1, kind=None)`: returns a sorted copy of the array.
  - `a`: input array.
  - `axis`: axis along which to sort (default -1, the last axis). Use `None` to sort the flattened array.
  - `kind`: sorting algorithm — `'quicksort'`, `'mergesort'`, `'heapsort'`, `'stable'`.

```python
unsorted = np.array([3, 1, 4, 1, 5, 9, 2])
sorted_arr = np.sort(unsorted)
print("Unsorted:", unsorted)    # original unchanged
print("Sorted:", sorted_arr)    # [1, 1, 2, 3, 4, 5, 9]

mat = np.array([[3, 1], [2, 4]])
print("Sort each row:", np.sort(mat, axis=1))  # [[1, 3], [2, 4]]
print("Sort each col:", np.sort(mat, axis=0))  # [[2, 1], [3, 4]]
```

### Sorting Indexes

- `np.argsort(a, axis=-1, kind=None)`: returns the indices that would sort the array.
  - `a`: input array.
  - `axis`: axis along which to sort (default -1).
  - `kind`: sorting algorithm (same options as `np.sort`).

```python
sort_indices = np.argsort(unsorted)
print("Sort indices:", sort_indices)                 # [1, 6, 3, 0, 2, 4, 5]
print("Sorted via indices:", unsorted[sort_indices]) # [1, 1, 2, 3, 4, 5, 9]
```

---

## Random Numbers

- `np.random.default_rng(seed=None)`: creates a new random number Generator (preferred modern API).
  - `seed`: integer seed for reproducibility. If `None`, the generator is randomly seeded.

- `rng.integers(low, high=None, size=None, dtype=np.int64)`: random integers from `low` (inclusive) to `high` (exclusive).
  - `low`: lower bound (inclusive).
  - `high`: upper bound (exclusive). If `None`, values are drawn from `[0, low)`.
  - `size`: shape of the output.

- `rng.random(size=None)`: uniform floats in `[0, 1)`.
  - `size`: shape of the output.

- `rng.standard_normal(size=None)`: samples from the standard normal distribution N(0, 1).
  - `size`: shape of the output.

- `rng.choice(a, size=None, replace=True, shuffle=True)`: random sample from an array or range.
  - `a`: input array or int (if int, samples from `np.arange(a)`).
  - `size`: shape of the output.
  - `replace`: whether sampling is with replacement.
  - `shuffle`: whether to shuffle the result.

Legacy API (still widely used):

- `np.random.randint(low, high=None, size=None, dtype=int)`: random integers (legacy).
- `np.random.rand(*d)`: uniform `[0, 1)` with shape `d` (legacy).
- `np.random.randn(*d)`: standard normal with shape `d` (legacy).
- `np.random.choice(a, size=None, replace=True)`: random sample (legacy).

```python
rng = np.random.default_rng(seed=42)           # reproducible generator

mat = rng.integers(0, 50, (3, 3))              # 3x3 matrix, integers in [0, 49]
rand1 = rng.random(3)                          # uniform [0, 1), shape (3,)
rand2 = rng.standard_normal(3)                 # N(0,1), shape (3,)
rand3 = rng.choice(np.arange(10), size=5, replace=False)  # 5 unique values from 0..9

print("Random integers:\n", mat)
print("Uniform [0,1):", rand1)
print("Standard normal:", rand2)
print("Choice (no replace):", rand3)

# Legacy API
rand_legacy = np.random.randint(0, 10, 5)  # random ints in [0, 9]
```

---

## Broadcasting

This allows NumPy to perform operations on arrays with different shapes by virtually expanding dimensions
to match the larger array's shape.

**Broadcasting rule**: two dimensions are compatible if they are equal or one of them is 1.

> Works: `(4, 4)` and `(4, 1)` — the second dimension of the second array is 1, so it broadcasts.

> Fails: `(2, 4)` and `(3, 5)` — no dimensions match or are 1.

When broadcasting applies, the smaller array is left-padded with size-1 dimensions until shapes match.

```python
arr = np.array([1, 2, 3]) # (1,3)
b = np.array([[4], [4]])  # (2,1)

print("Add scalar:", arr + 5)         # [6, 7, 8]
print("Multiply scalar:", arr * 2)    # [2, 4, 6]

# NumPy does deo following: 

# row expansion [1, 2, 3] -> [[1, 2, 3]] (1,3)
# -> [[1,2,3], [1,2,3]] (2, 3)
# b needs to be expanded to match the new shape 
# [[4], [4]] -> [[4, 4, 4], [4, 4, 4]] (2,3)
# Now  both have the same size

print("Complex expandion:", arr + b)  # [[5, 6, 7], [5, 6, 7]]

matrix = np.ones((3, 3))
vec = np.array([1, 2, 3])             # shape (3,) → broadcasts to (3, 3)
print("Matrix + row vector:\n", matrix + vec)

col_vec = np.array([[1], [2], [3]])   # shape (3, 1) → broadcasts to (3, 3)
print("Matrix + col vector:\n", matrix + col_vec)
```

### Boolean broadcasting with np.where

```python
ages = np.array([12, 24, 35, 45, 60, 72])
labels = np.array(["Minor", "Adult"])
result = np.where(ages > 18, labels[1], labels[0])
print("Labels:", result)  # ['Minor' 'Adult' 'Adult' 'Adult' 'Adult' 'Adult']
````

### Assignment broadcasting 

```python
arr = np.array([[1, 2, 3] for _ in range(3)])
arr[:,0] = 10 # assigning the value 10 to all of the first column element
```

---

## Array Manipulation

### Append, Insert & Delete

- `np.append(arr, values, axis=None)`: appends values to the end of an array.
  - `arr`: target arr 
  - `values`: values to be appended at a copy of arr. It must be the same shape as arr. If 
  axis is not specified, this arr gets flattend before use.
  - `axis`: Optional argument to specify along which axis values are appended.

- `np.insert(arr, obj, values, axis=None)`: inserts values along the given axis before the given indices.
  - `arr`: input array. 
  - `obj`: slice, list, etc. containing the index or indices before which values are inserted.
  - `values`: array of values to be inserted. 
  - `axis`: axis along which the values are inserted. If not specified then arr gets flattend.

- `np.delete(arr, obj, axis=None)`: returns a new array without the target of deletion.
  - `arr`: input array. 
  - `obj`: slice, list, etc. containing the index or indices of sub-arrays to remove along the specified axis. 
  -`axis`: the axis along which to delete the sub-array defined by obj. If axis is None, obj is applied to the flattened array. 

```python 

np.append([1, 2, 3], [[4, 5, 6], [7, 8, 9]])
# [1, 2, 3, 4, 5, 6, 7, 8 ,9]

np.append([[1, 2, 3], [4, 5, 6]], [[7, 8, 9]], axis=0)
#[[1, 2, 3],
# [4, 5, 6],
# [7, 8, 9]])

a = np.arange(6).reshape(3, 2)
# [[0, 1],
#  [2, 3],
#  [4, 5]]

np.insert(a, 1, 6)
# [0, 6, 1, 2, 3, 4, 5]

np. insert(a, 1, 6, axis=1)
# [0, 6, 1],
# [2, 6, 3],
# [4, 6, 5]]

arr = np.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]])
# [[ 1,  2,  3,  4],
#  [ 5,  6,  7,  8],
#  [ 9, 10, 11, 12]])

np.delete(arr, 1, 0)
# [[ 1,  2,  3,  4],
#  [ 9, 10, 11, 12]])

```

### Reshape, Flatten & Ravel

- `arr.reshape(shape)` or `np.reshape(a, newshape)`: changes the shape of the array without changing its data, as long as the total number of elements is preserved. Use `-1` for one dimension to let NumPy infer its size.
  - `shape`: tuple of ints defining the new shape.

- `arr.flatten(order='C')`: returns a 1D copy of the array.
  - `order`: `'C'` (row-major), `'F'` (column-major), `'A'` (Fortran if Fortran-contiguous, else C).

- `arr.ravel(order='C')`: returns a 1D array (a view if possible, otherwise a copy).
  - `order`: same as `flatten`.

- `np.transpose(a, axes=None)` or `arr.T`: reverses or permutes the axes of an array.
  - `a`: input array.
  - `axes`: tuple permuting the axes. If `None`, reverses all axes.

```python
arr = np.arange(12)

reshaped = arr.reshape(3, 4)        # 3 rows, 4 cols — same 12 elements
print("Reshaped (3x4):\n", reshaped)

auto_reshaped = arr.reshape(3, -1)  # NumPy infers 4 columns
print("Auto-reshaped (3x?):\n", auto_reshaped)

reshaped3d = arr.reshape(2, 3, 2)   # 3D: 2 blocks of 3x2
print("Reshaped (2,3,2):\n", reshaped3d)

flattened = reshaped.flatten()      # always a copy
print("Flattened:", flattened)

raveled = reshaped.ravel()          # view if possible
print("Raveled:", raveled)

col_vec = np.arange(4).reshape(-1, 1)  # shape (4, 1)
print("Column vector:\n", col_vec)

mat = np.array([[1, 2, 3], [4, 5, 6]])
print("Transposed:\n", mat.T)          # shape (3, 2)
```

### Removing Duplicates

- `np.unique(ar, return_index=False, return_inverse=False, return_counts=False, axis=None)`: returns the sorted unique elements of an array.
  - `ar`: input array.
  - `return_index`: if `True`, also returns the indices of the first occurrence of each unique value.
  - `return_inverse`: if `True`, also returns the indices to reconstruct the original array.
  - `return_counts`: if `True`, also returns the count of each unique value.
  - `axis`: axis along which to operate. If `None`, the array is flattened first.

```python
arr = np.array([3, 1, 2, 1, 3, 3, 2])
print("Unique:", np.unique(arr))  # [1, 2, 3]

unique_vals, counts = np.unique(arr, return_counts=True)
print("Unique:", unique_vals)  # [1, 2, 3]
print("Counts:", counts)       # [2, 2, 3]
```

### Concatenation & Stacking

- `np.concatenate((a1, a2, ...), axis=0)`: joins a sequence of arrays along an existing axis.
  - `(a1, a2, ...)`: tuple of arrays — must have the same shape except along `axis`.
  - `axis`: axis along which to concatenate (default 0).

- `np.vstack(tup)`: stacks arrays vertically (row-wise). Equivalent to `concatenate(..., axis=0)`.
  - `tup`: sequence of arrays — must have the same number of columns.

- `np.hstack(tup)`: stacks arrays horizontally (column-wise). Equivalent to `concatenate(..., axis=1)` for 2D arrays.
  - `tup`: sequence of arrays — must have the same number of rows.

- `np.dstack(tup)`: stacks arrays depth-wise (along the third axis).
  - `tup`: sequence of arrays.

- `np.column_stack(tup)`: stacks 1D arrays as columns into a 2D array, or 2D arrays column-wise. Very useful when combining features and labels.
  - `tup`: sequence of 1D or 2D arrays.

```python
a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6]])

concat = np.concatenate((a, b), axis=0)     # same as vstack here
print("Concatenated (axis=0):\n", concat)   # [[1,2],[3,4],[5,6]]

stacked_v = np.vstack((a, b))
print("Vertically stacked:\n", stacked_v)   # [[1,2],[3,4],[5,6]]

col = np.array([[7], [8]])
stacked_h = np.hstack((a, col))
print("Horizontally stacked:\n", stacked_h) # [[1,2,7],[3,4,8]]

stacked_d = np.dstack((a, a))
print("Depth stacked shape:", stacked_d.shape)  # (2, 2, 2)

x = np.array([1, 2, 3])
y = np.array([4, 5, 6])
print("Column stack:\n", np.column_stack((x, y)))  # [[1,4],[2,5],[3,6]]
```

### Blocks

NumPy blocks allow us to construct matrices from other matrices as building blocks.
The only requirement is that dimensions match along the joining direction.

- `np.block(arrays)`: assembles an nd-array from a nested list of blocks.
  - `arrays`: nested list of arrays forming the block matrix.

```python
# Build a block matrix:
# [2I | 0 ]
# [1  | 3I]
b = np.block([
    [np.eye(2) * 2,   np.zeros((2, 3))],
    [np.ones((3, 2)), np.eye(3) * 3   ]
])
print("Block matrix:\n", b)
```

### Sub-matrices

NumPy provides tools for extracting and constructing diagonal and triangular sub-matrices.

- `np.diag(v, k=0)`: if `v` is 1D, constructs a 2D array with `v` on the k-th diagonal; if `v` is 2D, extracts the k-th diagonal as a 1D array.
  - `v`: 1D array to place on the diagonal, or 2D array to extract from.
  - `k`: diagonal offset — `0` is the main diagonal, positive is above, negative is below.

- `np.diagonal(a, offset=0, axis1=0, axis2=1)`: returns the specified diagonal without copying.
  - `a`: input array (at least 2D).
  - `offset`: diagonal offset (same convention as `np.diag`).
  - `axis1`, `axis2`: the two axes that define the 2D sub-space from which the diagonal is taken.

- `np.tril(m, k=0)`: returns the lower triangle of a matrix — all elements above the k-th diagonal are set to zero.
  - `m`: input matrix.
  - `k`: diagonal cutoff; `0` keeps the main diagonal.

- `np.triu(m, k=0)`: returns the upper triangle of a matrix — all elements below the k-th diagonal are set to zero.
  - `m`: input matrix.
  - `k`: diagonal cutoff.

- `np.fill_diagonal(a, val, wrap=False)`: fills the main diagonal of `a` **in-place**.
  - `a`: input array (at least 2D), modified directly.
  - `val`: scalar or sequence to fill the diagonal with.
  - `wrap`: if `True`, wraps diagonally for tall matrices.

```python
mat = np.array([[1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]])

# Extract main diagonal
print("Main diagonal:", np.diag(mat))          # [1, 5, 9]
print("Above-main diagonal:", np.diag(mat, k=1))  # [2, 6]
print("Below-main diagonal:", np.diag(mat, k=-1)) # [4, 8]

# Build a diagonal matrix from a 1D array
print("Diag matrix from [1,2,3]:\n", np.diag([1, 2, 3]))
# [[1, 0, 0],
#  [0, 2, 0],
#  [0, 0, 3]]

# Lower and upper triangles
print("Lower triangle:\n", np.tril(mat))
# [[1, 0, 0],
#  [4, 5, 0],
#  [7, 8, 9]]

print("Upper triangle:\n", np.triu(mat))
# [[1, 2, 3],
#  [0, 5, 6],
#  [0, 0, 9]]

print("Lower (k=1):\n", np.tril(mat, k=1))  # includes one super-diagonal

# Fill diagonal in-place
A = np.zeros((3, 3))
np.fill_diagonal(A, [1, 2, 3])
print("Filled diagonal:\n", A)
# [[1., 0., 0.],
#  [0., 2., 0.],
#  [0., 0., 3.]]

# Cholesky decomposition: A = L @ L.T (requires positive-definite matrix)
A_pd = np.array([[4.0, 2.0], [2.0, 3.0]])
L = np.linalg.cholesky(A_pd)
print("Cholesky L:\n", L)
print("L @ L.T:\n", L @ L.T)  # ≈ A_pd
```

### Index-Based Array Creation

- `arr[np.where(condition)]`: creates an array from the elements where a condition is satisfied.

```python
arr = np.array([10, 20, 30, 40, 50])
result = arr[np.where(arr > 25)]
print("Elements > 25:", result)  # [30, 40, 50]
```

### Clip

- `np.clip(a, a_min, a_max, out=None)`: limits the values in an array to the range `[a_min, a_max]`.
  - `a`: input array.
  - `a_min`: minimum value — values below this are set to `a_min`.
  - `a_max`: maximum value — values above this are set to `a_max`.

```python
arr = np.array([-3, -1, 0, 2, 5, 8])
print("Clipped:", np.clip(arr, 0, 5))  # [0, 0, 0, 2, 5, 5]
```

---

## Element-Wise Operations

```python
arr10 = np.array([1, 2, 3])
arr11 = np.array([4, 5, 6])

print("Add:", arr10 + arr11)           # [5, 7, 9]
print("Subtract:", arr11 - arr10)      # [3, 3, 3]
print("Multiply:", arr10 * arr11)      # [4, 10, 18]
print("Power:", arr10 ** arr11)        # [1, 32, 729]
print("Divide:", arr11 / arr10)        # [4.0, 2.5, 2.0]
print("Floor divide:", arr11 // arr10) # [4, 2, 2]
print("Modulo:", arr11 % arr10)        # [0, 1, 0]
```

---

## Scalar Operations (Simple Broadcasting)

```python
arr = np.array([1, 2, 3])

print("Scalar multiplication:", arr * 2)   # [2, 4, 6]
print("Scalar addition:", arr + 2)         # [3, 4, 5]
print("Scalar power:", arr ** 2)           # [1, 4, 9]
print("Square root:", np.sqrt(arr))        # [1.0, 1.414, 1.732]
print("Absolute value:", np.abs(arr - 5)) # [4, 3, 2]
```

---

## Aggregate Functions

- `arr.sum(axis=None)` or `np.sum(a, axis=None)`: sum of array elements.
  - `axis`: axis along which to sum. If `None`, sums all elements.

- `arr.mean(axis=None)` or `np.mean(a, axis=None)`: arithmetic mean.
  - `axis`: axis along which to compute the mean.

- `arr.max(axis=None)` or `np.max(a, axis=None)`: maximum value.
  - `axis`: axis along which to find the max.

- `arr.min(axis=None)` or `np.min(a, axis=None)`: minimum value.
  - `axis`: axis along which to find the min.

- `arr.prod(axis=None)` or `np.prod(a, axis=None)`: product of all elements.
  - `axis`: axis along which to compute the product.

- `arr.cumsum(axis=None)`: cumulative sum of elements.
  - `axis`: axis along which to accumulate. If `None`, works on the flattened array.

```python
arr = np.array([[1, 2, 3], [4, 5, 6]])

print("Total sum:", arr.sum())                   # 21
print("Column-wise sum (axis=0):", arr.sum(axis=0))  # [5, 7, 9]
print("Row-wise sum (axis=1):", arr.sum(axis=1))     # [6, 15]
print("Mean:", arr.mean())                       # 3.5
print("Max:", arr.max())                         # 6
print("Min:", arr.min())                         # 1
print("Product:", arr.prod())                    # 720
print("Cumulative sum:", arr.cumsum())           # [1, 3, 6, 10, 15, 21]
```

---

## Mathematical Functions

NumPy provides universal functions (ufuncs) for element-wise mathematical operations.

```python
# Exponential & logarithm
print("exp:", np.exp(np.array([0, 1, 2])))         # [1.0, e, e²]
print("log (natural):", np.log(np.array([1, np.e])))  # [0.0, 1.0]
print("log2:", np.log2(np.array([1, 2, 4])))       # [0.0, 1.0, 2.0]
print("log10:", np.log10(np.array([1, 10, 100])))  # [0.0, 1.0, 2.0]

# Rounding
arr = np.array([1.2, 1.5, 1.7, -1.2, -1.7])
print("floor:", np.floor(arr))  # [ 1.,  1.,  1., -2., -2.]
print("ceil:", np.ceil(arr))    # [ 2.,  2.,  2., -1., -1.]
print("round:", np.round(arr))  # [ 1.,  2.,  2., -1., -2.]
print("abs:", np.abs(arr))      # [1.2, 1.5, 1.7, 1.2, 1.7]

# Square root & power
print("sqrt:", np.sqrt(np.array([4, 9, 16])))      # [2., 3., 4.]
print("power:", np.power(np.array([2, 3]), 3))     # [8, 27]
```

---

## Trigonometry

NumPy uses **radians** by default. Use `np.deg2rad()` and `np.rad2deg()` to convert.

```python
angles_deg = np.array([0, 30, 45, 60, 90, 180])
angles_rad = np.deg2rad(angles_deg)

print("sin:", np.sin(angles_rad))   # [0.0, 0.5, 0.707, 0.866, 1.0, 0.0]
print("cos:", np.cos(angles_rad))   # [1.0, 0.866, 0.707, 0.5, 0.0, -1.0]
print("tan:", np.tan(angles_rad))   # [0.0, 0.577, 1.0, 1.732, large, 0.0]

# Inverse trig (output in radians)
print("arcsin:", np.arcsin(np.array([0, 0.5, 1])))   # [0.0, π/6, π/2]
print("arccos:", np.arccos(np.array([1, 0.5, 0])))   # [0.0, π/3, π/2]
print("arctan:", np.arctan(np.array([0, 1])))        # [0.0, π/4]
print("arctan2(y=1, x=1):", np.arctan2(1, 1))        # π/4

# Hyperbolic
print("sinh:", np.sinh(np.array([0, 1])))  # [0.0, 1.175]
print("cosh:", np.cosh(np.array([0, 1])))  # [1.0, 1.543]
print("tanh:", np.tanh(np.array([0, 1])))  # [0.0, 0.762]

# Convert back to degrees
print("π/2 in degrees:", np.rad2deg(np.pi / 2))  # 90.0
```

---

## Statistical Functions

- `np.mean(a, axis=None)`: arithmetic mean.
  - `a`: input array.
  - `axis`: axis to reduce.

- `np.median(a, axis=None)`: median value (middle value when sorted).
  - `a`: input array.
  - `axis`: axis to reduce.

- `np.var(a, axis=None, ddof=0)`: variance.
  - `a`: input array.
  - `axis`: axis to reduce.
  - `ddof`: delta degrees of freedom (use `ddof=1` for sample variance).

- `np.std(a, axis=None, ddof=0)`: standard deviation.
  - `a`: input array.
  - `axis`: axis to reduce.
  - `ddof`: delta degrees of freedom (use `ddof=1` for sample std).

- `np.min(a, axis=None)` / `np.max(a, axis=None)`: minimum / maximum value.
  - `a`: input array.
  - `axis`: axis to reduce.

- `np.ptp(a, axis=None)`: peak-to-peak (max − min).
  - `a`: input array.
  - `axis`: axis to reduce.

- `np.percentile(a, q, axis=None)`: returns the q-th percentile.
  - `a`: input array.
  - `q`: percentile value(s) in the range [0, 100].
  - `axis`: axis to reduce.

- `np.quantile(a, q, axis=None)`: same as percentile but `q` is in the range [0, 1].
  - `a`: input array.
  - `q`: quantile value(s) in the range [0, 1].

- `np.argmax(a, axis=None)`: returns the index of the maximum value.
  - `a`: input array.
  - `axis`: axis along which to operate.

- `np.argmin(a, axis=None)`: returns the index of the minimum value.
  - `a`: input array.
  - `axis`: axis along which to operate.

```python
arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])

print("Mean:", np.mean(arr))              # 5.0
print("Median:", np.median(arr))          # 5.0
print("Variance:", np.var(arr))           # 6.666...
print("Std Dev:", np.std(arr))            # 2.581...
print("Min:", np.min(arr))               # 1
print("Max:", np.max(arr))               # 9
print("Range (ptp):", np.ptp(arr))       # 8

print("25th percentile:", np.percentile(arr, 25))  # 3.0
print("50th percentile:", np.percentile(arr, 50))  # 5.0
print("75th percentile:", np.percentile(arr, 75))  # 7.0

print("Quantiles:", np.quantile(arr, [0, 0.25, 0.5, 0.75, 1]))  # [1. 3. 5. 7. 9.]

print("Index of max:", np.argmax(arr))   # 8
print("Index of min:", np.argmin(arr))   # 0
```

### Covariance and Correlation

- `np.cov(m, y=None, rowvar=True, ddof=1)`: estimates the covariance matrix.
  - `m`: 1D or 2D array — each row is a variable, each column is an observation.
  - `y`: additional set of variables with the same shape as `m`.
  - `rowvar`: if `True` (default), each row is a variable; if `False`, each column is.
  - `ddof`: delta degrees of freedom (default 1 for an unbiased estimate).

- `np.corrcoef(x, y=None, rowvar=True)`: Pearson correlation coefficient matrix, values in `[-1, 1]`.
  - `x`: 1D or 2D array of variables.
  - `y`: additional set of variables.
  - `rowvar`: if `True` (default), each row is a variable.

```python
x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])  # perfect linear relationship

print("Covariance matrix:\n", np.cov(x, y))
# [[ 2.5  5. ]
#  [ 5.  10. ]]

print("Correlation matrix:\n", np.corrcoef(x, y))
# [[1. 1.]
#  [1. 1.]]  (perfect positive correlation)
```

### Standardization & Z-Scores

```python
arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
z_scores = (arr - np.mean(arr)) / np.std(arr)
print("Z-scores:", z_scores)
# Mean of z-scores ≈ 0, std ≈ 1
```

### Random Sampling

```python
rng = np.random.default_rng(42)
arr = np.arange(1, 10)

rand_sample = rng.choice(arr, size=5, replace=False)
print("Sample (no replacement):", rand_sample)

rand_sample_repl = rng.choice(arr, size=5, replace=True)
print("Sample (with replacement):", rand_sample_repl)

# Bootstrap sampling (resampling with replacement, same size as original)
bootstrap = rng.choice(arr, size=len(arr), replace=True)
print("Bootstrap sample:", bootstrap)
```

---

## Calculus

### Numerical Differentiation

- `np.gradient(f, *varargs, axis=None, edge_order=1)`: computes the numerical gradient using central differences in the interior and first/second-order accurate one-sided differences at the boundaries.
  - `f`: input array (sampled values of the function).
  - `*varargs`: spacing between samples — a single scalar for uniform spacing, or one 1D coordinate array per axis. If omitted, spacing of 1 is assumed.
  - `axis`: axis or axes along which to compute the gradient. If `None`, the gradient is computed along all axes and a list of arrays is returned.
  - `edge_order`: accuracy at the boundary — `1` (first-order, default) or `2` (second-order).

- `np.diff(a, n=1, axis=-1, prepend=np._NoValue, append=np._NoValue)`: computes the n-th discrete difference along the given axis (finite forward differences).
  - `a`: input array.
  - `n`: order of differentiation — `1` for first differences, `2` for second differences (approximates the second derivative), etc.
  - `axis`: axis along which to compute (default `-1`, the last axis).
  - `prepend` / `append`: values to add before/after `a` before computing differences (useful to control the output shape).

### Numerical Integration

- `np.trapezoid(y, x=None, dx=1.0, axis=-1)`: integrates `y(x)` using the composite trapezoidal rule. Each pair of adjacent samples forms a trapezoid whose area is summed.
  - `y`: array of function values.
  - `x`: array of sample positions. If `None`, uniform spacing of `dx` is assumed.
  - `dx`: spacing between samples when `x` is not given (default `1.0`).
  - `axis`: axis along which to integrate (default last axis).

> Note: `np.trapz` is the legacy name (deprecated in NumPy 2.0). Use `np.trapezoid` for NumPy ≥ 2.0.

- `np.cumsum(a, axis=None, dtype=None)`: cumulative sum — each output element is the sum of all preceding input elements. Approximates the anti-derivative via a Riemann sum when multiplied by the step size.
  - `a`: input array.
  - `axis`: axis along which to accumulate. If `None`, operates on the flattened array.

### Grid Creation

- `np.meshgrid(*xi, indexing='xy', sparse=False, copy=True)`: creates coordinate matrices from coordinate vectors. Used to evaluate functions over a 2D (or higher-dimensional) grid.
  - `*xi`: 1D arrays representing coordinates along each axis.
  - `indexing`: `'xy'` (Cartesian, default — first output varies along columns) or `'ij'` (matrix/NumPy indexing — first output varies along rows).
  - `sparse`: if `True`, returns open (sparse) grids instead of full broadcast grids — much more memory-efficient for high-dimensional grids.
  - `copy`: if `False`, may return views of the input arrays.

### Polynomials

- `np.polyfit(x, y, deg, rcond=None, full=False, w=None, cov=False)`: least-squares polynomial fit. Returns coefficients `[pn, ..., p1, p0]` for a degree-`deg` polynomial.
  - `x`: x-coordinates of the data points.
  - `y`: y-coordinates of the data points.
  - `deg`: degree of the fitting polynomial.
  - `w`: weights for the data points (optional).
  - `cov`: if `True`, also returns the covariance matrix of the coefficient estimates.

- `np.polyval(p, x)`: evaluates a polynomial at given points.
  - `p`: 1D array of polynomial coefficients in descending order `[pn, ..., p1, p0]`.
  - `x`: scalar or array of points at which to evaluate.

- `np.poly1d(c_or_r, r=False, variable=None)`: represents a polynomial as an object supporting arithmetic, evaluation, differentiation and integration.
  - `c_or_r`: coefficients in descending order, or roots if `r=True`.
  - `r`: if `True`, `c_or_r` is interpreted as the polynomial roots.

- `np.polyder(p, m=1)`: returns the derivative of a polynomial.
  - `p`: polynomial coefficients or `poly1d` object.
  - `m`: order of differentiation (default 1).

- `np.polyint(p, m=1, k=None)`: returns the anti-derivative of a polynomial.
  - `p`: polynomial coefficients or `poly1d` object.
  - `m`: order of integration (default 1).
  - `k`: integration constants (default 0 for each order).

### Convolution

- `np.convolve(a, v, mode='full')`: discrete, linear convolution of two 1D sequences.
  - `a`, `v`: 1D input arrays.
  - `mode`: `'full'` (full output, length `len(a)+len(v)-1`), `'same'` (output has same length as `a`), `'valid'` (only where the sequences fully overlap).

```python
# --- Numerical Differentiation ---

# First derivative of sin(x) → cos(x)
x = np.linspace(0, 2 * np.pi, 200)
f = np.sin(x)
dfdx = np.gradient(f, x)                    # uses actual x spacing
print("df/dx at π/2 ≈", dfdx[50])          # ≈ cos(π/2) ≈ 0

# np.diff — forward differences
y = np.array([0.0, 1.0, 4.0, 9.0, 16.0])   # f(x) = x² at x = 0,1,2,3,4
dy = np.diff(y)                              # [1, 3, 5, 7] — first differences
d2y = np.diff(y, n=2)                        # [2, 2, 2]    — second differences ≈ f''=2
print("First diff:", dy)
print("Second diff:", d2y)

# Keep the same length with prepend
dy_full = np.diff(y, prepend=y[0])           # same length as y
print("First diff (same length):", dy_full)

# --- Numerical Integration ---

# ∫₀^π sin(x) dx = 2
x_int = np.linspace(0, np.pi, 1000)
y_int = np.sin(x_int)
integral = np.trapezoid(y_int, x_int)
print("∫₀^π sin(x) dx ≈", integral)         # ≈ 2.0

# Cumulative integral (Riemann sum approximation)
dx = x_int[1] - x_int[0]
cumulative = np.cumsum(y_int) * dx
print("Cumulative integral at π:", cumulative[-1])  # ≈ 2.0

# --- Grid Creation ---

x_vals = np.linspace(-np.pi, np.pi, 50)
y_vals = np.linspace(-np.pi, np.pi, 50)
X, Y = np.meshgrid(x_vals, y_vals)           # both shape (50, 50)
Z = np.sin(X) * np.cos(Y)
print("Grid shape:", X.shape)                # (50, 50)
print("Z range: [{:.2f}, {:.2f}]".format(Z.min(), Z.max()))

# 2D gradient of the scalar field Z
dZ_dy, dZ_dx = np.gradient(Z, y_vals, x_vals)  # note: returns [axis0, axis1]
print("∂Z/∂x shape:", dZ_dx.shape)            # (50, 50)

# Sparse grid — memory-efficient
X_s, Y_s = np.meshgrid(x_vals, y_vals, sparse=True)
print("Sparse X shape:", X_s.shape)          # (1, 50)
print("Sparse Y shape:", Y_s.shape)          # (50, 1)
Z_s = np.sin(X_s) * np.cos(Y_s)             # broadcasting still works

# Matrix ('ij') indexing
Xi, Yi = np.meshgrid(x_vals, y_vals, indexing='ij')  # first index → rows
print("Matrix indexing shape:", Xi.shape)             # (50, 50)

# --- Polynomials ---

# Fit a degree-2 polynomial to noisy data
rng = np.random.default_rng(0)
x_data = np.linspace(-3, 3, 50)
y_data = 2 * x_data**2 - x_data + 3 + rng.standard_normal(50)
coeffs = np.polyfit(x_data, y_data, deg=2)
print("Fitted coefficients:", np.round(coeffs, 2))  # ≈ [2, -1, 3]

# Evaluate the fitted polynomial
x_eval = np.linspace(-3, 3, 200)
y_fit = np.polyval(coeffs, x_eval)

# poly1d object — supports arithmetic and derivative/integral
p = np.poly1d(coeffs)
print("p(0) =", p(0))            # ≈ 3
print("p'(x):", np.polyder(p))   # derivative: degree-1 polynomial
print("∫p dx:", np.polyint(p))   # anti-derivative: degree-3 polynomial

# --- Convolution ---

# Smooth a signal with a box filter
signal = np.array([1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0])
kernel = np.array([1/3, 1/3, 1/3])
smoothed = np.convolve(signal, kernel, mode='same')
print("Smoothed signal:", np.round(smoothed, 2))

# Polynomial multiplication via convolution:
# (x + 1)(x + 2) = x² + 3x + 2
poly_a = np.array([1, 1])   # x + 1
poly_b = np.array([1, 2])   # x + 2
print("Product coefficients:", np.convolve(poly_a, poly_b))  # [1, 3, 2]
```


## Splitting

- `np.vsplit(ary, indices_or_sections)`: splits an array into multiple sub-arrays vertically (row-wise).
  - `ary`: input array.
  - `indices_or_sections`: int (number of equal splits) or 1D array of split indices.

- `np.hsplit(ary, indices_or_sections)`: splits an array into multiple sub-arrays horizontally (column-wise).
  - `ary`: input array.
  - `indices_or_sections`: int or 1D array of split indices.

- `np.repeat(a, repeats, axis=None)`: repeats elements of an array.
  - `a`: input array.
  - `repeats`: int or array of ints — number of times each element is repeated.
  - `axis`: axis along which to repeat. If `None`, the array is flattened first.

- `np.tile(A, reps)`: constructs an array by tiling (repeating) `A`.
  - `A`: input array.
  - `reps`: int or tuple — number of repetitions along each axis.

```python
arr = np.arange(9).reshape(3, 3)
print("Original:\n", arr)

split_rows = np.vsplit(arr, 3)         # 3 separate arrays of shape (1, 3)
print("Vsplit:", [s.shape for s in split_rows])

split_cols = np.hsplit(arr, 3)         # 3 separate arrays of shape (3, 1)
print("Hsplit:", [s.shape for s in split_cols])

arr2 = np.array([1, 2, 3])
print("Repeat each element 2x:", np.repeat(arr2, 2))  # [1, 1, 2, 2, 3, 3]
print("Tile array 3x:", np.tile(arr2, 3))             # [1, 2, 3, 1, 2, 3, 1, 2, 3]
print("Tile as 2x3:", np.tile(arr2, (2, 3)))          # [[1,2,3,1,2,3,1,2,3],[...]]
```

---

## Linear Algebra

- `np.dot(a, b)`: dot product of two arrays. For 2D arrays, equivalent to matrix multiplication.
  - `a`, `b`: input arrays.

- `a @ b`: matrix multiplication operator (equivalent to `np.matmul(a, b)`). Preferred over `np.dot` for matrices.

- `np.outer(a, b)`: outer product of two 1D arrays — produces an `(N, M)` matrix.
  - `a`: 1D array of length N.
  - `b`: 1D array of length M.

- `np.linalg.det(a)`: determinant of a square matrix.
  - `a`: square matrix (N×N).

- `np.cross(a, b, axisa=-1, axisb=-1, axisc=-1, axis=None)`: cross product of two (arrays of) vectors. For 3D vectors returns a 3D vector perpendicular to both; for 2D vectors returns the scalar z-component.
  - `a`, `b`: input arrays. The vectors must be 2D or 3D (length 2 or 3 along the relevant axis).
  - `axisa`, `axisb`: axes of `a` and `b` that define the vectors (default last axis).
  - `axisc`: axis of the output array that holds the cross product vector.
  - `axis`: if given, sets `axisa`, `axisb`, and `axisc` simultaneously.

- `np.linalg.inv(a)`:   multiplicative inverse of a square matrix.
  - `a`: square non-singular matrix.

- `np.linalg.eig(a)`: eigenvalues and right eigenvectors of a square matrix.
  - `a`: square matrix.
  - Returns: `(eigenvalues, eigenvectors)` — each column of `eigenvectors` is an eigenvector.

- `np.linalg.eigh(a, UPLO='L')`: eigenvalues and eigenvectors of a **symmetric** (or Hermitian) matrix. Faster and more numerically stable than `np.linalg.eig` for symmetric inputs. Eigenvalues are returned in ascending order.
  - `a`: symmetric or Hermitian square matrix. Only the lower or upper triangle is used.
  - `UPLO`: `'L'` to read the lower triangle (default), `'U'` for the upper triangle.
  - Returns: `(eigenvalues, eigenvectors)` — columns of `eigenvectors` are the orthonormal eigenvectors.

- `np.linalg.matrix_rank(M, tol=None)`:   matrix rank computed via SVD.
  - `M`: matrix to evaluate.
  - `tol`: threshold below which singular values are considered zero.

- `np.linalg.norm(x, ord=None, axis=None)`: matrix or vector norm.
  - `x`: input array.
  - `ord`: type of norm (e.g., `2` for Euclidean, `'fro'` for Frobenius, `np.inf` for max absolute row sum).
  - `axis`: axis along which to compute the norm.

- `np.linalg.solve(a, b)`: solves the linear system `a @ x = b`.
  - `a`: coefficient matrix (N×N, must be non-singular).
  - `b`: ordinate array (shape N or N×M).

- `np.linalg.svd(a, full_matrices=True)`: Singular Value Decomposition — factorizes `a` into `U @ diag(s) @ Vh`.
  - `a`: input matrix.
  - `full_matrices`: if `True`, returns full-sized U and Vh.

- `np.trace(a, offset=0, axis1=0, axis2=1, dtype=None, out=None):` If `a` is a 2d array it returns the diagonal sum, else returns an array of sums along the diagonals.
  - `a`: input matrix.
  - `offset`: offset of the diagonal from the main diagonal.
  - `axis1=0, axis2=1`: axes used for 2D diagonal sum, given that the array has a higher dimension. 
  - `dtype`: determines the data type of the returned array or accumulator
  - `out`: array into which the output is placed,

```python
arr1 = np.array([1, 2, 3])
arr2 = np.array([4, 5, 6])

print("Dot product:", np.dot(arr1, arr2))          # 32
print("Outer product:\n", np.outer(arr1, arr2))    # 3x3 matrix

mat = np.array([[1, 2], [3, 4]])
mat2 = np.array([[5, 6], [7, 8]])

print("Matrix multiply (@):\n", mat @ mat2)        # [[19,22],[43,50]]
print("Determinant:", np.linalg.det(mat))          # -2.0
print("Inverse:\n", np.linalg.inv(mat))

eigvals, eigvecs = np.linalg.eig(mat)
print("Eigenvalues:", eigvals)
print("Eigenvectors:\n", eigvecs)

# Diagonalization: A = P D P⁻¹
D = np.diag(eigvals)
P = eigvecs
reconstructed = P @ D @ np.linalg.inv(P)
print("Reconstructed matrix:\n", np.round(reconstructed))  # ≈ [[1,2],[3,4]]

# Solve Ax = b
A = np.array([[3, 1], [1, 2]])
b = np.array([9, 8])
x = np.linalg.solve(A, b)
print("Solution x:", x)                            # [2. 3.]

print("Frobenius norm:", np.linalg.norm(mat))      # ≈ 5.477
print("Euclidean norm of vec:", np.linalg.norm(arr1))  # ≈ 3.742

# SVD
U, s, Vh = np.linalg.svd(mat)
print("Singular values:", s)

# Low-rank approximation using SVD (keep top k singular values)
k = 1
mat_approx = (U[:, :k] * s[:k]) @ Vh[:k, :]
print("Rank-1 approximation:\n", mat_approx)

# Rank and condition number
print("Rank:", np.linalg.matrix_rank(mat))
print("Condition number:", np.linalg.cond(mat))    # ratio of largest to smallest singular value

# Cross product
a3d = np.array([1, 0, 0])   # unit x vector
b3d = np.array([0, 1, 0])   # unit y vector
print("Cross product (x × y):", np.cross(a3d, b3d))  # [0, 0, 1] — unit z vector

a2d = np.array([1, 2])
b2d = np.array([3, 4])
print("2D cross product (scalar):", np.cross(a2d, b2d))  # 1*4 - 2*3 = -2

# eigh — symmetric matrix (faster than eig, real eigenvalues)
sym = np.array([[4.0, 2.0], [2.0, 3.0]])
eigvals_h, eigvecs_h = np.linalg.eigh(sym)
print("Eigenvalues (eigh):", eigvals_h)   # ascending order, guaranteed real
print("Eigenvectors (eigh):\n", eigvecs_h)

# Verify: A v = λ v for each eigenpair
for i in range(len(eigvals_h)):
    residual = sym @ eigvecs_h[:, i] - eigvals_h[i] * eigvecs_h[:, i]
    print(f"Residual {i}:", np.linalg.norm(residual))   # ≈ 0

# Trace (sum of diagonal elements = sum of eigenvalues)
print("Trace:", np.trace(mat))            # 5 = 1 + 4
```

### Transpose & Swap Axes

- `arr.T` or `np.transpose(a, axes=None)`: reverses the axes of an array.
  - `a`: input array.
  - `axes`: if specified, a permutation of axis indices (e.g., `(2, 0, 1)` for a 3D array).

- `arr.swapaxes(axis1, axis2)`: interchanges two axes.
  - `axis1`, `axis2`: axes to swap.

```python
mat = np.array([[1, 2, 3], [4, 5, 6]])
print("Original shape:", mat.shape)    # (2, 3)
print("Transposed:\n", mat.T)          # shape (3, 2)

arr3d = np.arange(24).reshape(2, 3, 4)
print("Original shape:", arr3d.shape)                               # (2, 3, 4)
print("Swapaxes(0,2) shape:", arr3d.swapaxes(0, 2).shape)           # (4, 3, 2)
print("Transpose(2,0,1) shape:", np.transpose(arr3d, (2, 0, 1)).shape)  # (4, 2, 3)
```

---

## Input & Output

- `np.loadtxt(fname, delimiter=None, dtype=float, skiprows=0, usecols=None)`: loads data from a text file.
  - `fname`: file path or file object.
  - `delimiter`: string separating values (e.g., `','`).
  - `dtype`: data type for the resulting array.
  - `skiprows`: number of rows to skip at the beginning.
  - `usecols`: columns to read (e.g., `(0, 2)` for the first and third columns).

- `np.savetxt(fname, X, delimiter=' ', fmt='%.18e', header='')`: saves an array to a text file.
  - `fname`: file path.
  - `X`: 1D or 2D array to save.
  - `delimiter`: string separating columns.
  - `fmt`: format string for each element (e.g., `'%d'` for integers, `'%.4f'` for 4 decimal places).

- `np.genfromtxt(fname, delimiter=None, dtype=float, filling_values=np.nan, names=None)`: loads data from a text file, handling missing values gracefully.
  - `fname`: file path.
  - `delimiter`: string separating values.
  - `filling_values`: value used for missing entries.
  - `names`: if `True`, reads column names from the first valid line.

- `np.save(file, arr)`: saves a single array to a binary `.npy` file.
  - `file`: file path (`.npy` extension is added automatically).
  - `arr`: array to save.

- `np.load(file)`: loads a `.npy` or `.npz` file.
  - `file`: path to the file.

- `np.savez(file, **kwargs)`: saves multiple arrays to a compressed `.npz` archive.
  - `file`: file path (`.npz` is added automatically).
  - `**kwargs`: named arrays to save.

```python
arr = np.array([[1, 2, 3], [4, 5, 6]])

# Text files
np.savetxt('data.csv', arr, delimiter=',', fmt='%d')
loaded = np.loadtxt('data.csv', delimiter=',')
print("Loaded from CSV:\n", loaded)

data = np.genfromtxt('data.csv', delimiter=',', filling_values=0)

# Binary files (faster and lossless)
np.save('array.npy', arr)
loaded_npy = np.load('array.npy')
print("Loaded from .npy:\n", loaded_npy)

# Multiple arrays in one file
np.savez('arrays.npz', a=arr, b=arr * 2)
archive = np.load('arrays.npz')
print("Keys:", list(archive.keys()))  # ['a', 'b']
print("a:\n", archive['a'])
```

---

## Vectorized Operations

Many operations in NumPy act on whole arrays instead of single elements, avoiding the overhead of Python loops.

- `np.vectorize(pyfunc, otypes=None, excluded=None)`: vectorizes a Python function so it accepts array input.
  - `pyfunc`: the Python function to vectorize.
  - `otypes`: output data types (optional, e.g., `[float]`).
  - `excluded`: set of argument names or indices that are not vectorized.

```python
def is_even(x):
    return 1 if x % 2 == 0 else 0

vec_is_even = np.vectorize(is_even)

arr = np.arange(10)
print("Even mask:", vec_is_even(arr))  # [1, 0, 1, 0, 1, 0, 1, 0, 1, 0]

# For simple cases, direct array operations are faster than np.vectorize
even_mask = (arr % 2 == 0).astype(int)
print("Even mask (direct):", even_mask)  # same result
```

---

## Custom Datatypes

NumPy supports structured arrays with custom field names and types.

```python
# Basic dtype declaration
dt = np.dtype(np.int32)
print("dtype:", dt)

# Structured array (like a table with named columns)
person_dtype = np.dtype([('name', 'U20'), ('age', np.int32), ('score', np.float64)])
people = np.array([('Alice', 30, 95.5), ('Bob', 25, 87.2)], dtype=person_dtype)
print("Names:", people['name'])   # ['Alice' 'Bob']
print("Ages:", people['age'])     # [30 25]
print("Scores:", people['score']) # [95.5 87.2]
```

---

## Type Conversion

- `arr.astype(dtype)`: casts the array to a different data type.
  - `dtype`: target data type (e.g., `np.float64`, `np.int32`, `np.bool_`).

```python
arr = np.array([1.7, 2.9, 3.1])
print("As int:", arr.astype(np.int32))    # [1, 2, 3] — truncates, does not round
print("As bool:", arr.astype(np.bool_))   # [True, True, True]

int_arr = np.array([0, 1, 255], dtype=np.uint8)
print("uint8:", int_arr)
print("As float32:", int_arr.astype(np.float32))  # [0.0, 1.0, 255.0]
```
