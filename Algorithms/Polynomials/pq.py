import numpy as np

"""
Given cx^2 + px + q = 0 

Compute x_1, x_2 = -p -+ sqrt{p^2 + q}
"""
def pq_formula_1(pol):
    
    c = pol[0]
    p = pol[1] 
    q = pol[2] 

    if  c != 1:
        c /= c 
        p /= c 
        q /= c 
    
    x_1 = (-1)*p - np.sqrt(np.pow(p, 2) + q)
    x_2 = (-1)*p + np.sqrt(np.pow(p, 2) + q)

    return (x_1, x_2) 



"""
Given cx^2 + px + q = 0 

Compute x_1 = -p - sqrt{p^2 + q}
        x_2 = frac{-q}{x_1}
"""
def pq_formula_2(pol):
    
    c = pol[0]
    p = pol[1] 
    q = pol[2] 

    if  c != 1:
        c /= c 
        p /= c 
        q /= c 
    
    x_1 = (-1)*p - np.sqrt(np.pow(p, 2) + q)
    x_2 = (-1)*q / x_1

    return (x_1, x_2) 



print(pq_formula_1((1, 10**2, 1)), pq_formula_2((1, 10**2, 1)))
print(pq_formula_1((1, 10**4, 1)), pq_formula_2((1, 10**4, 1)))
print(pq_formula_1((1, 10**6, 1)), pq_formula_2((1, 10**6, 1)))
print(pq_formula_1((1, 10**7, 1)), pq_formula_2((1, 10**7, 1)))
print(pq_formula_1((1, 10**8, 1)), pq_formula_2((1, 10**8, 1)))








