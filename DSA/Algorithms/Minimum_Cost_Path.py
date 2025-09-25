

def minimum_cost_path(matrix):
    
    cost = [[0 for _ in range(0, len(matrix[0]))] for _ in range(0, len(matrix))]
    
    for i in range(0, len(matrix)):

        for j in range(0, len(matrix[0])):

            if i != 0 or j != 0:

                t = cost[i - 1][j] if i > 0 else float('inf')
                l = cost[i][j - 1] if j > 0 else float('inf')
                cost[i][j] = matrix[i][j] + min(t, l)


    return cost[len(matrix)- 1][len(matrix[0]) - 1]

def minimum_cost_path_rec(matrix: list[list[int]]):
    
    n = len(matrix) - 1
    m = len(matrix[0]) - 1

    def rec(i: int, j: int, memo):
        
        if (i, j) in memo:
            return memo[(i,j)]

        if i == n and j == m:
            return matrix[i][j]
        
        if i > n or j > m:
            return float('inf')

        r = rec(i, j + 1, memo)
        b = rec(i + 1, j, memo)         
        memo[(i,j)] = matrix[i][j] + min(b, r)

        return memo[(i,j)]

    return rec(0, 0, {})


print(minimum_cost_path_rec([[1]]))
print(minimum_cost_path_rec([[1,2],[8,4]]))
