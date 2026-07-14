from typing import List

"""
Given an integer array nums sorted in non-decreasing order, remove 
the duplicates in-place such that each unique element appears only once. 
The relative order of the elements should be kept the same.
"""
def removeDuplicates(arr: List[int]) -> int:

    if len(arr) == 0:
        return 0

    j = 0;

    for i, num in enumerate(arr):   
        
        # If the check is redudant: j = i - 1, then the swap does nothing, if the difference of the indeces is greater then it 
        # swaps the elements properly.
        if arr[j] != num:
            j += 1
            t = arr[j]
            arr[j] = arr[i]
            arr[i] = t

    return j + 1

"""
Remove all occurrences of the val in-place inside the array and return the new length
"""

# Inneficient
def removeElement(nums, val):
 
    j = len(nums) - 1
    i = 0
    
    while i <= j:
        
        # Condition for the swapping
        if nums[i] == val:
            
            # get the index of the last element != val which is after i
            # if j == i the swap does nothing
            while nums[j] == val and j > i:
                j -= 1
            
            # swap
            nums[i] = nums[j]
            
            # no matter the case of the while loop we decrement j accordingly
            j -= 1
        
        i += 1
    
    # since if the last decrement moves us pass the limit we add one to it
    return j + 1

# Efficient
def removeElement2(arr: List[int], val: int) -> int:
    idx = 0 
    for i in range(len(arr)):
        if arr[i] != val:
            arr[idx] = arr[i]
            idx += 1
    return idx
