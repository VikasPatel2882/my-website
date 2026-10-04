class Solution(object):
    def checkValidString(self, s):
        """
        :type s: str
        :rtype: bool
        """
        min_open = 0
        max_open = 0
        
        for char in s:
            if char == '(':
                min_open += 1
                max_open += 1
            elif char == ')':
                min_open -= 1
                max_open -= 1
            else:  # char == '*'
                min_open -= 1  # treating '*' as ')'
                max_open += 1  # treating '*' as '('
            
            # More ')' than '(' + '*' encountered so far
            if max_open < 0:
                return False
            
            # min_open cannot be negative (we cannot have a negative count of open brackets)
            if min_open < 0:
                min_open = 0
                
        return min_open == 0