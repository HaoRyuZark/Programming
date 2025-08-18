
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
def longest_increasin_subsequence(nums:list[int]) -> int:
   
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
- If characters match at i and j, we include that character and move diagonally.
- If not, we explore both skipping a character in text1 or text2 and take the max.

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
            if text1[i] == text2[j]:
                lens[i][j] = 1 + lens[i + 1][j + 1]
            else:
                lens[i][j] = max(lens[i][j + 1], lens[i + 1][j])
    
    return lens[0][0]


def main():

    print(fib_of_n(50, {}))
    print(fib(50))
    print(minimum_coins(150, [1, 4, 5], {}))

main()
