class Solution(object):
    def minSwaps(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def digit_sum(n):
            return sum(int(d) for d in str(n))
        
        n = len(nums)
        # Pair each number with its index
        indexed_nums = [(nums[i], i) for i in range(n)]
        
        # Sort based on digit sum, then by value
        indexed_nums.sort(key=lambda x: (digit_sum(x[0]), x[0]))
        
        # Find the minimum swaps using cycle sort / permutation cycles
        visited = [False] * n
        swaps = 0
        
        for i in range(n):
            if visited[i] or indexed_nums[i][1] == i:
                continue
            
            # Traverse the cycle
            cycle_size = 0
            curr = i
            while not visited[curr]:
                visited[curr] = True
                curr = indexed_nums[curr][1]
                cycle_size += 1
                
            if cycle_size > 1:
                swaps += (cycle_size - 1)
                
        return swaps