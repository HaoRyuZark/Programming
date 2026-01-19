import numpy as np 
import pandas as pd 

"""
    Performs gradient descent optimization.

    Parameters:
    f               : function to minimize
    grad_f          : gradient (derivative) of f
    initial_x       : starting point
    learning_rate   : step size (how big each update is)
    num_iterations  : number of iterations to run

    Returns:
    x               : value that minimizes f
    history         : list of x values during optimization
"""
def gradient_descent(f, grad_f, initial_x, learning_rate, num_iterations):
    
    # Start from the initial guess
    x = initial_x

    # Store the history of x values (optional)
    history = []

    for i in range(num_iterations):

        # Compute the gradient (slope) of the function at current x
        gradient = grad_f(x)

        # Update x by moving *against* the gradient
        x = x - learning_rate * gradient

        # Save the current value of x
        history.append(x)

    return x, history


# Define the function
def f(x):
    return x ** 2

# Define its gradient
def grad_f(x):
    return 2 * x


minimum_x, history = gradient_descent(
    f=f,
    grad_f=grad_f,
    initial_x=10,        # starting far from minimum
    learning_rate=0.1,   # step size
    num_iterations=20
)

print("Minimum found at x =", minimum_x)


