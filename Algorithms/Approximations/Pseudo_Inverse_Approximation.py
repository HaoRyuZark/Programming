import numpy as np 
import matplotlib.pyplot as plt 

# Initial Matrix
def get_A(n=100, gamma=0.05):

    def a_ij(i, j):
        return (1 / gamma * np.sqrt(2 * np.pi)) / np.exp(i - j / np.sqrt(2)*n*gamma)

    return np.array([[a_ij(i, j) for j in range(n)] for i in range(n)])

A = get_A()

print(f"A: \n{A}\n")

def get_x(n=100):
    def get_xi(i):
        if i >= 45 and i <= 55: 
            return 1 
        if i >= 60 and i <= 65: 
            return 1/2
        return 0 

    return np.array([get_xi(i) for i in range(n)])

x = get_x()

print(f"x: \n{x}\n")

b = A @ x

print(f"b: \n{b}\n")


def distord_b(b, n = 100, delta=10e-6):
    return b - delta * np.random.randn(n)

delta_b = distord_b(b)

print(f"b distord: \n{delta_b}\n")


# a) 

monda = np.linalg.pinv(A) @ (b + delta_b)

print(f"A^+ (b + delta_b) (monda): \n{monda}\n")

# b)

n, m = A. shape
u, s, q = np.linalg.svd(A)

print(f"u shape: \n{u.shape}\n")
print(f"s shape: \n{s.shape}\n")
print(f"q shape: \n{q.shape}\n")
print(f"u: \n{u}\n")
print(f"s: \n{s}\n")
print(f"q: \n{q}\n")

first_sv = s[0]

print(f"First singular value: {first_sv}\n")

for p in range(0, -9, -1):

    alpha = 10**p
    boundary = np.sqrt(alpha)

    for k in range(len(s) - 1):

        if (s[k] / first_sv >= boundary) and (s[k + 1] / first_sv < boundary):

            s_alpha = np.zeros((n, m))

            for j in range(k + 1):
                s_alpha[j, j] = 1 / s[j]

            x_a = q.T @ s_alpha @ u.T @ b

            print(f"alpha = {alpha}")
            print(f"k = {k + 1}")
            print(f"x_a =\n{x_a}\n")

            break
