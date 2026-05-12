import numpy as np 
import math

def _find_max(i, n, matrix): 
    max_idx = -1
    max = float("inf")

    for j in range(i + 1, n):
        if matrix[j][i] > max and matrix[j][i] != 0:
            max = matrix[j][i]
            max_idx = j

    return max_idx

def _permute_pivot(i, n, matrix, p): 
    j = _find_max(i, n, matrix) 
    matrix[[i, j]] = matrix[[j, i]]
    p[i], p[j] = p[j], p[i]

def _permute(i, n, matrix, p):
    for j in range(i + 1, n):
        if matrix[j][i] != 0:
            matrix[[i, j]] = matrix[[j, i]]
            p[i], p[j] = p[j], p[i]
            break

def _permute_b(b, p):
    return b[p]

def _solve_Ly(matrix, b, n):
    y = np.zeros(n)
    for i in range(n):
        s = 0
        for j in range(i):
            s += matrix[i][j] * y[j]
        y[i] = b[i] - s

    return y

def _solve_Ux(matrix, y, n):
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        s = 0
        for j in range(i + 1, n):
            s += matrix[i][j] * x[j]
        x[i] = (y[i] - s) / matrix[i][i]

    return x

def lu_decomposition(matrix, b):

    if np.linalg.det(matrix) == 0 or np.shape(matrix)[0] != np.shape(matrix)[1]:
        raise Exception("Not a fitting matrix")

    matrix = matrix.astype(float)
    n, m = matrix.shape

    p = np.arange(n)

    for i in range(0, n - 1):

        if matrix[i][i] == 0:
            _permute(i, n, matrix, p)

        for j in range(i + 1, n):

            if matrix[j][i] == 0:
                continue

            l_ik = matrix[j][i] / matrix[i][i]
            matrix[j][i] = l_ik

            for k in range(i + 1, n):
                matrix[j][k] -= l_ik * matrix[i][k]

    b = _permute_b(b, p)
    y = _solve_Ly(matrix, b, n)
    x =  _solve_Ux(matrix, y, n)
    
    return after_iteration(get_L(matrix), get_U(matrix), x, b, epsi=0.001)
    

def get_L(matrix):
    L = np.copy(matrix) 
    n, m = matrix.shape

    for i in range(0, n):
        for j in range(i, n):
                L[i][j] = 0    
        L[i][i] = 1
    return L

def get_U(matrix):
    U = np.copy(matrix) 
    n, m = matrix.shape

    for i in range(1, n):
        for j in range(0, i):
            U[i][j] = 0
    return U

def magnitude(vector): 
    return math.sqrt(sum(pow(element, 2) for element in vector))

def after_iteration(L, U, x, b, epsi):

    A = L @ U
    x_k = x.copy()

    while True:
        r_k = b - A @ x_k
        p_k = np.linalg.solve(A, r_k)
        x_k += p_k

        if magnitude(p_k) / magnitude(x_k) < epsi:
            break

    return x_k

def test_2by2():
    A2 = [[2, 3],
          [4, 7]]

    b2 = [5, 11]

    x2 = np.array([1, 1])

    x_test = lu_decomposition(np.array(A2), np.array(b2))

    return x_test == x2

def test_3by3():
    A3 = [[2, -1, 1],
          [3,  3, 9],
          [3,  3, 5]]

    b3 = [-1, 0, 4]

    x3 = np.array([1, 2, -1])

    x_test = lu_decomposition(np.array(A3), np.array(b3))

    return x_test == x3

print(f"Test result test_2by2: {test_2by2()} and test_3by3: {test_3by3()}")
