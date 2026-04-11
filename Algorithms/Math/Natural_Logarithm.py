import numpy as np 

def ln_migux(x: np.float64, n: int):
    s = 0.0
    for k in range(1, n + 1):
        s += ((-1)**(k + 1)) * (x**k) / k
    return s

print(f'Migux {ln_migux(np.float64(0.9), 50)} Numpy: {np.log(np.float64(0.9) + 1)}')
