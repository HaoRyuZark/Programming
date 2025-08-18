import copy
from typing import List
'''
Backtracking
 
Is a programming technique use to solve problems in which we may need to step back to solve a problem.

It is brute force but elegant.
  
Template:
    - State -> valid(fine) / invalid -> backtrack

# Additional functions my be needed depending on the problem

def is_valid_state(state): # check if we do not break a condition
    return True


def get_candidates(state): # get next possible choices
    return []


def search(state, solutions): # recursive function to go deep in the choice-tree

    if is_valid_state(state): # solution found
        solutions.append(state.copy())
        #return if we need one we return else we continue search for all solutions

    for candidate in get_candidates(state): # searching the solution
        state.add(candidate)                # choice
        search(state, solutions)            # recursive call we the need state
        state.remove(candidate)             # remove last added state (backtrack step !!!!!!!)
                                            # if search leads us a solution or invalid state we want to make sure to continue we a different
                                            # choice. Basiclly un-doing our decision.

def solve():  # Wrapper function
    
    solutions = []
    state = set()
    search(state, solutions)

    return solutions

Simplified Steps:
    Start
    Choose: Make a decision 
    Move Forward: Continue the decicion path
    End Point: Meet a dead end (?). Dont allow duplicates
    Go back: Return to the last decision

Use cases:
    Choice problems
    Optimization
    Enumeration
'''

'''
Example 1 find all subsets of a set
'''

from typing import Tuple
    
def find_subsets(nums):

    def backtrack(start, current):
        
        result.append(list(current))
        
        for i in range(start, len(nums)):

            if i > start and nums[i] == nums[i - 1]:
                continue

            current.append(nums[i])
            backtrack(i + 1, current)

            current.pop()
    
    result = []

    nums.sort()

    backtrack(0, [])

    return result


'''
 Example 2: N-Queens problem

 Not the most optimal in space, but the best to understand :)
'''
def n_queens(board, n):
    
    solutions:list = []

    search(board, solutions, n, 0)

    return solutions

def check_attack(state: list[list[str]], pos: Tuple[int, int], n: int) -> bool:
    
    pos_row = pos[0]
    pos_col = pos[1]

    #Check same column
    for i in range(0, n):
        
        if i != pos_row and state[i][pos_col] == 'Q':
            return False
            
 
    #Check same row
    for i in range(0, n):
        
        if i != pos_col and state[pos_row][i] == 'Q':
            return False
    
    #Check right diagonals
    for i in range(1,n):
    
        # Upper-right diagonal (↗)
        row = pos_row - i
        col = pos_col + i
        
        if 0 <= row < n and 0 <= col < n:
            if state[row][col] == 'Q':
                return False

        # Lower-right diagonal (↘)
        row = pos_row + i
        col = pos_col + i
        
        if 0 <= row < n and 0 <= col < n:
            if state[row][col] == 'Q':
                return False
   
    # Check left diagonals
    for i in range(1, n):
        
        # Upper-left diagonal (↖)
        row = pos_row - i
        col = pos_col - i
        
        if 0 <= row < n and 0 <= col < n:
            if state[row][col] == 'Q':
                return False

        # Lower-left diagonal (↙)
        row = pos_row + i
        col = pos_col - i
        
        if 0 <= row < n and 0 <= col < n:
            if state[row][col] == 'Q':
                return False

    return True

def search(state: list[list[str]], solutions: list[list[list[str]]], n:int, row:int):

    if row == n:
        solutions.append(copy.deepcopy(state))   # solution found
         

    for col in range(0,n):                       # iterate over columns

        if check_attack(state, (row, col), n):   # allowing only valid moves
                
            state[row][col] = 'Q'                # creating a new state (choice)
            search(state, solutions, n, row + 1) # recursive call with the new state it just returns if there is dead end
            state[row][col] = '.'                # backtrack step 


def search_optimized(n:int) -> list[list[str]]:

    cols = set()
    pos_diagonal = set() # (r + c)
    neg_diagonal = set() # (r - c)
    
    res = []
    board = [["."] * n for i in range(n)]

    def backtrack(r):
        
        if r == n:
            copy = ["".join(row) for row in board]
            res.append(copy)
            return

        for c in range(n):

            if c in cols or (r + c) in pos_diagonal or (r - c) in neg_diagonal:
                continue

            cols.add(c)
            pos_diagonal.add(r + c)
            neg_diagonal.add(r - c)
            board[r][c] = "Q"

            backtrack(r + 1)

            cols.remove(c)
            pos_diagonal.remove(r + c)
            neg_diagonal.remove(r - c)
            board[r][c] = "."
 
    backtrack(0)

    return res


'''
Example combinations

Given two integers n and k return all possible combinations of k numbers in the range [1,n]

Example:
    
    n = 4, k = 2,
    
    [
        [2,3],
        [2,4],
        [1,3],
        ... 
    ]
'''
def combinations(n:int, k:int) -> list[list[int]]:
    
    res:list[list[int]] = []

    if k > n:
        return res
    if k == n:
        return [[i for i in range(1,n)]]

    current = []

    def backtrack(start, current):
        
        if (len(current) ==  k):
            res.append(copy.deepcopy(current))
            return

        for i in range(start,n):

                current.append(i)
                backtrack(i + 1, current)
                current.pop()

    backtrack(1, current)
     
    return res


def minimum_coins(sum, coins):

    
    def backtrack(current_sum, length):
        
        if current_sum == sum:
            lengths.append(length)
            return
        
        if current_sum > sum:
            return

        for coin in coins:
            backtrack(current_sum + coin, length + 1)                
        
            
    
    lengths = []
    backtrack(0,0)

    return min(lengths) if lengths else -1


def has_path(adj_list, start, end, len):

    def backtrack(path, current_len, current_node):
        
        if current_len == len and current_node == end:
            return True
        
        if current_len != len:
            return False

        for node in adj_list[current_node]:
            
            path.append(node)
            
            if backtrack(path, len + 1, node):
                return True

            path.pop()

        return False

    path = []
    result = backtrack(path, start, 0)

    return (result, path if result else [])


'''
Givena n x m matrix with zeroes and ones go from [0][0] to [n -1][m - 1]. You can only travel 
cells which contain a 0. The rest are ones.
'''

def find_path(matrix: list[list[int]]) -> list[list[int]]:

    # Return value
    path = [[-1 for _ in range(len(matrix[0]))] for _ in range(len(matrix))]
    n = len(matrix)
    m = len(matrix[0])


    def backtrack(row, col):
        
        if row >= n or col >= m or matrix[row][col] != 0:
            return False


        path[row][col] = 0
        
        if row == n - 1 and col == m - 1:
            return True

        if backtrack(row, col + 1) or backtrack(row + 1, col):
            return True

        path[row][col] = -1
        return False
    
    backtrack(0, 0)
    return path

'''
Find all permutations of a set of numbers
'''
def permute(nums: List[int]) -> List[List[int]]:

    res = []

    def backtrack(state: List[int]):
        if len(state) == len(nums):
            res.append(state[:])  # Append a copy
            return

        for i in range(len(nums)):
            if nums[i] not in state:
                state.append(nums[i])
                backtrack(state)
                state.pop()

    n = len(nums)
    backtrack([])  # Start with an empty state
    return res

def main():
    n = 4
    board = [['.' for _ in range(n)] for _ in range(n)]
    solutions = n_queens(board, n)

    for sol in solutions:
        for row in sol:
            print("".join(row))
        print()



main()
