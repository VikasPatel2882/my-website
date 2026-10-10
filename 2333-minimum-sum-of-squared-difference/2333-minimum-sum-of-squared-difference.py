from collections import Counter

class Solution(object):
    def minSumSquareDiff(self, nums1, nums2, k1, k2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k1: int
        :type k2: int
        :rtype: int
        """
        n = len(nums1)
        total_k = k1 + k2
        
        # Step 1: Compute absolute differences and their frequencies
        diff_counts = Counter(abs(nums1[i] - nums2[i]) for i in range(n))
        
        # Find the maximum difference to start our downward traversal
        max_diff = max(diff_counts.keys()) if diff_counts else 0
        
        # Step 2: Greedily reduce the largest differences
        for d in range(max_diff, 0, -1):
            if diff_counts[d] == 0:
                continue
            
            # Number of operations needed to reduce all elements with difference 'd' down to 'd - 1'
            count = diff_counts[d]
            operations_needed = min(total_k, count)
            
            total_k -= operations_needed
            diff_counts[d] -= operations_needed
            diff_counts[d - 1] += operations_needed
            
            # If we run out of operations, we can stop early
            if total_k == 0:
                break
        
        # Step 3: Compute the final sum of squared differences
        ans = 0
        for d, count in diff_counts.items():
            ans += (d * d) * count
            
        return ans