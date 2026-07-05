from typing import List

'''
Two Sum

Find the two indices of the numbers in an array that add up to a given target.
The original can not be modified
'''


def two_sum(nums: List[int], target: int) -> List[int]:

    found = {} # to store index of the nums[i]: Pair<Amount, Index> 

    for i, num in enumerate(nums): # iterate over list
        
        s = target - num # get the complement

        if s in found:    # if the complement is a key -> found 
            return [i, found[s]] # return pair
        else:
            found[num] = i  # complement no in hashmap -> store index of the number

    return [] # No solution found


print(two_sum([2, 7, 11, 15], 9)) # [1, 0]



