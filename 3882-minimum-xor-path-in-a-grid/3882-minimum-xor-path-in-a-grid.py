class Solution(object):
    def minCost(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        
        # dp[i][j] will store a set of all possible XOR values to reach cell (i, j)
        dp = [[set() for _ in range(n)] for _ in range(m)]
        
        # Initialize the starting cell
        dp[0][0].add(grid[0][0])
        
        for i in range(m):
            for j in range(n):
                # If there are values from the top cell (i-1, j)
                if i > 0:
                    for val in dp[i - 1][j]:
                        dp[i][j].add(val ^ grid[i][j])
                
                # If there are values from the left cell (i, j-1)
                if j > 0:
                    for val in dp[i][j - 1]:
                        dp[i][j].add(val ^ grid[i][j])
                        
        # The answer is the minimum XOR value at the bottom-right cell (m - 1, n - 1)
        return min(dp[m - 1][n - 1])