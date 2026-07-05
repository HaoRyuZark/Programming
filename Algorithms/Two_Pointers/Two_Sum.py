from typing import List

'''
Two Sum

Find the two indices of the numbers in an array that add up to a given target.
The original can not be modified. This time the array is sorted in ascending order.
'''

def two_sum(nums: List[int], target: int) -> List[int]:

    left, right = 0, len(nums) - 1

    while left < right:

        dif = nums[right] - nums[left]

        if dif == target:
            return [left, right]
        elif dif < target:
            left += 1
        else:
            right -= 1
        
    return []

 
print(two_sum([2, 7, 11, 15], 9)) # [0, 1]


