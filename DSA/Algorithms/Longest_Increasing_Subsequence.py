
def longest_increasing_subsequence(nums: list[int]) -> int:
   
    lis = [1] * len(nums)
    n = len(nums) - 1;

    for i in range(n, -1, -1):

        for j in range(i + 1, n):
            
            if nums[i] < nums[j]:
                lis[i] = max(lis[i], 1 + lis[j])

    return max(lis)


        

