class Solution(object):
    def targetIndices(self, nums, target):
        """:type nums: List[int]"""
        """:type target: int"""
        """:rtype: List[int]"""
        count_less = 0
        count_target = 0
        
        for num in nums:
            if num < target:
                count_less += 1
            elif num == target:
                count_target += 1
                
        return list(range(count_less, count_less + count_target))