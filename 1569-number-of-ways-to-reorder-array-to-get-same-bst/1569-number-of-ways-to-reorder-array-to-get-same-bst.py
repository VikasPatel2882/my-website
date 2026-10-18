class Solution(object):
    def numOfWays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def count_ways(arr):
            if len(arr) <= 2:
                return 1
            root = arr[0]
            left = [x for x in arr if x < root]
            right = [x for x in arr if x > root]
            
            # Using standard factorial-based combination calculation for compatibility
            ways = self.comb(len(left) + len(right), len(left), MOD) % MOD
            return (ways * count_ways(left) * count_ways(right)) % MOD

        return (count_ways(nums) - 1) % MOD

    def comb(self, n, k, mod):
        if k < 0 or k > n:
            return 0
        if k == 0 or k == n:
            return 1
        if k > n // 2:
            k = n - k
        
        numerator = 1
        denominator = 1
        for i in range(k):
            numerator = (numerator * (n - i)) % mod
            denominator = (denominator * (i + 1)) % mod
            
        return (numerator * pow(denominator, mod - 2, mod)) % mod