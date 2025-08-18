from typing import List

'''
Two Sum

Find the two indeces of the numbers in an array that add up to a given target.
The original can no be modified
'''


def twoSum(self, nums: List[int], target: int) -> List[int]:

    found = {} # to store index of the nums[i]: Pair<Amount, Index> 

    for i, num in enumerate(nums): # iterate over list
        
        s = target - num # get the complement

        if s in found:    # if the complement is a key -> found 
            return [i, found[s]] # return pair
        else:
            found[num] = i  # complement no in hashmap -> store index of the number

    return [] # No solution found


