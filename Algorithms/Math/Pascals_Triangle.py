def pascals_triangle(n: int):

    for i in range(n + 1):
        coef = 1
        
        # Print leading spaces for formatting
        print(" " * (n - i), end="")
        
        # Print the coefficients
        for k in range(i + 1):
            
            print(f"{int(coef)} ", end="")
            coef = coef * (i - k) / (k + 1) # (n over k + 1) = (i over  k) * (i - k)/(k + 1)

        print()  # Newline after each row

