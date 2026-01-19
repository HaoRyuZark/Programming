'''
Dynamic Programming

Big Idea: Recursion + (Memoization or Tabulation) -> Rememberring solutions to subproblems

Techniques: Memoization, Tabulation

Common use-cases:
    -> Finding an optimal solution of many
    -> Counting the total number of solutions
    -> Many More

General Steps:
    1. Visulize: Tree, Graph, recurrence relations etc
    2. Find an appropiate subsproblem -> until the simplest case
    3. Find relationships amoung subsproblems and sort them via topological sort (in your head not in code)
    4. Get a working solution (Generalization of subsproblems): Mostly using backtracking and recursion
    5. Use a Dynamic Programming Techniques to optimize


Top-down-Approach -> Memoization
Start with the big problem and the solve the subproblems

Bottom-up Approach -> Tabulation
Start with the subproblems to then solve the big problem

Memoization -> Recursion
Means rememberring. With this technique we can skip repeated computations

Tabulation -> Iteration
Comes from table and is meant to be used as such for storing previous calculations

Step:
    1. Identify where do computations repeat themselfs
    2. Add a dictionary(Hash-Map)
    3. Store the computations in the dictionary
    4. If the result of a computations is already is the memo return the value


'''

# Fibonnaci with Memoization Top-down-Approach
def fib_of_n(num, memo):
    
    if num in memo:
        return memo[num]

    if num <= 2:
        return 1;
    else:
        memo[num] = fib_of_n(num - 1, memo) + fib_of_n(num - 2,memo)
    
    return memo[num]

# Fibonnaci with Tabulation Bottom-up-Approach
def fib(num):

    memo = {}

    for i in range(1, num + 1):
        
        if i <= 2:
            memo[i] = 1
        else:
            memo[i] = memo[i - 1] + memo[i - 2]

    return memo[num]


'''
 Goal get the length of the longest sequence of number of the form  i < j < k where
 they dont need to be next to each other in the array

What do we know?

-> We have to iterate over the array at leas one time

-> We will have some repetition in the computations -> store precalculated values

-> We have two choices:
    1. Include the next number if current < next -> procedure(nums, i + 1, len + 1) -|
                                                                                     |-> Does not need to be recursion
    2. Skip -> procedure(nums, i + 1, len) ------------------------------------------|

-> The last index is not interessting during the outer loop because it has no next number. 

-> We need a way to store the previous lengths -> a table for all numsber in nums -> can be used for lookups

-> Beacuase a number is bigger than other it does not mean that it always will be the best choice skiping can help -> max(take, skip)

-> Visualization for:  6    1           4       0       5
                          / | \       /  \      |
                        4   0  5     0   5      5
                      /  \   \      /
                     0    5   5    5
                     |
                     5
Longest = 3

-> Algorithm:

    - Make a table of the size of the array with each index stores the value one.
    - Interate over the array backwards starting
    - Inside the firts loop write another loop which check if a element on the right of the current index is greater than itself
    - If that is the case then we take the max of (length[i], 1 + length[j]) which means the length of the current subsequence or 
      the sequence starting from the next index plus the current position.
    - After the outer loop finishes return the max of the table

'''
def longest_increasing_subsequence(nums:list[int]) -> int:
   
    n = len(nums)
    table = [1] * n

    for i in range(n - 1, -1, -1):   # iterate over the array backwards

        for j in range(i + 1, n):   # iterate the array from one more than our start position to the end
            if nums[i] < nums[j]:   # if the numbers are less then -> 
                table[i] = max(table[i], table[j] + 1) # choose max between the length of the subsequence starting from i or the 
                                                       # and the length one from j plus 1 (our position)
    return max(table)

def min_ignore_None(answer, subproblem):
    
    if answer is None:
        return subproblem
    
    if subproblem is None:
        return answer

    return min(answer, subproblem)

def minimum_coins(sum, coins, memo) -> int:
    
    if sum in memo[sum]:
        return memo[sum]

    if sum == 0:
        answer = 0
    else:

        answer = None
        
        for coin in coins:
            subproblem = sum - coin

            if subproblem < 0:
                continue

            answer = min_ignore_None(answer, minimum_coins(subproblem, coins, memo)+1)
        
    
    memo[sum] = answer
    return memo[sum]

def minimum_coins_iter(sum, coins, memo) -> int:

    memo[0] = 0
    
    for i in range(1, sum + 1):
        
        for coin in coins:
            subproblem = i - coin

            if subproblem < 0:
                continue

            memo[i] = min_ignore_None(memo.get(i), memo.get(subproblem) + 1)

    return memo[sum]

def how_many_ways(sum, coins) -> int:
    
    table = [0] * (sum + 1) #table entry for all number starting from 0
    table[0] = 1  # base case 1 way

    for coin in coins:
                    
        for amount in range(coin, sum + 1):
            
            table[amount] = table[amount - coin]

    return table[sum]


'''
Number of ways of traversing a maze when we only can move either right or down
'''
def maze(n: int, m: int) -> int:
    
    table = {}

    for i in range(1, n + 1):
        table[(i, 1)] = 1

    for j in range(1, m + 1):
        table[(1, j)] = 1


    for i in range(2, n + 1):
        for j in range(2, m + 1):
            
            table[i,j] = table[(i - 1, j)] + table[(i, j - 1)]


    return table[(n,m)]


'''
This function calculates the length of the Longest Common Subsequence (LCS)
between two input strings using dynamic programming.

------------------------
Intuition:
------------------------

A subsequence is a sequence that appears in the same relative order, but not
necessarily contiguously. The goal is to find the maximum number of characters
that both strings share *in order*.

We use a bottom-up dynamic programming approach:

- Define lens[i][j] as the length of the LCS between text1[i:] and text2[j:].
- We start from the end of both strings and work backwards.
- If characters match at i and j, we include that character and move diagonally. This means we do not have to check the subscases
- If not, we explore both skipping a character in text1 [i + 1][j] or text2 [i][j + 1] and take the max of their longest common subsequence.

This avoids recomputation and builds up the solution efficiently.

The key is that if a character matches then we would move diagonal accross the table.
For the case when the characters do not match then it is necessary to either move right or down. 
Moving right means looking at the character right of the missmatch of the text2 and moving down the same 
but with text1. 

We start from the bottom to use the precalculated values efficiently.
------------------------
Example:
    text1 = "abcde"
    text2 = "ace"

The DP table (lens) would be filled like this:

      a  c  e
    ---------
  a| 3  2  1
  b| 2  2  1
  c| 2  2  1
  d| 1  1  1
  e| 1  1  1
   | 0  0  0

Rows correspond to characters in "abcde" (text1), and columns to "ace" (text2).
Each cell (i, j) holds the LCS length of text1[i:] and text2[j:].

Final result = lens[0][0] = 3 (The LCS is "ace")
'''
def longest_common_subsequence(text1: str, text2: str) -> int:
    
    n = len(text1)
    m = len(text2)

    # Initialize the DP table with 0s
    lens = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
    
    # Fill the table from bottom right to top left
    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):
            
            # If there is math include the char and proced
            if text1[i] == text2[j]:
                lens[i][j] = 1 + lens[i + 1][j + 1]

            # If there is no match then take the max of the previous lcs
            else:
                lens[i][j] = max(lens[i][j + 1], lens[i + 1][j])
    
    return lens[0][0]


"""
Floyd-Warshall Algorithm — All-Pairs Shortest Paths

This algorithm computes the shortest paths between all pairs of nodes
in a weighted graph, including negative edge weights (but not negative cycles).

Use Case:
    - Solving all-pairs shortest path problems efficiently using dynamic programming.

Graph Representation:
    - The graph should be represented as an adjacency matrix.
    - Use float('inf') to represent the absence of a direct connection between nodes.

Predecessor Matrix:
    - A separate matrix is used to track the predecessors of each node in the shortest path.
    - Initially, for every edge (i, j) with a finite weight, set predecessor[i][j] = i.

Algorithm Steps:
    1. Initialize a distance matrix based on the input adjacency matrix.
    2. Initialize a predecessor matrix based on direct connections.
    3. For each node k (used as an intermediate node):
        - For each pair of nodes (i, j):
            - If going from i to j via k is shorter than the current known distance:
                - Update distance[i][j] = distance[i][k] + distance[k][j]
                - Update predecessor[i][j] = predecessor[k][j]

Edge Case Handling:
    - After all iterations, check if any diagonal entry in the distance matrix is negative.
    - A negative value on the diagonal indicates a negative cycle in the graph.

Example:
    Given:
        node = 1, row = 2, column = 4
        A[2][4] = ∞
        A[2][1] = 8
        A[1][4] = 7

    Since 8 + 7 < ∞, update:
        A[2][4] = 15
        P[2][4] = P[1][4]
"""
def floyd_warshall(graph: list[list[int]], distances: list[list[int]], pred: list[list[int]]):

    for vertex in range(0, len(graph)):

        for row in range(0, len(graph)):

            for col in range(0, len(graph)):

                new_dist = distances[row][vertex] + distances[vertex][col] 

                if new_dist < distances[row][col]:

                    distances[row][col] = new_dist
                    pred[row][col] = pred[vertex][col]


'''
Minimum cost for traversing a grid when moving only down and right
'''
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
print(fib_of_n(50, {}))
print(fib(50))
print(minimum_coins(150, [1, 4, 5], {}))

