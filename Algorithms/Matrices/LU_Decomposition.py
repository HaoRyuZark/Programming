import numpy as np 


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

    return _solve_Ux(matrix, y, n)

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
