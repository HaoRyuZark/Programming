
'''
Divide and conquer is a programming technique usually used to improve the 
performance of algoritms by divinding the problem into smaller subproblems of the same nature.

It consists of the steps:
    - Divide : Divides the problem recursively until the minimum size is found  
    - Solve : Solves the smallest possible subproblem 
    - Merge : Combines all solutions to get the final answer 
'''

'''
Example: Finding the max and min of an array at the same time 
'''

def minmax(nums:list[int], start: int, end: int) -> list[int]:
    
    if end - start <= 2:
        mx = max(nums[end], nums[start])
        mn = min(nums[end], nums[start])

        return [mx, mn]
    
    else:
        med = (end - start) // 2 

        mm1 = minmax(nums, med, end) 
        mm2 = minmax(nums, start, med) 

        return [max(mm1[0], mm2[0]), min(mm1[1], mm2[1])]
        

