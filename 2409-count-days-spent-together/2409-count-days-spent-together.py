class Solution(object):
    def countDaysTogether(self, arriveAlice, leaveAlice, arriveBob, leaveBob):
        """
        :type arriveAlice: str
        :type leaveAlice: str
        :type arriveBob: str
        :type leaveBob: str
        :rtype: int
        """
        days_in_months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        def date_to_day_number(date_str):
            month, day = map(int, date_str.split('-'))
            # Sum up days of previous months + current day
            total_days = sum(days_in_months[:month - 1]) + day
            return total_days
        
        start_alice = date_to_day_number(arriveAlice)
        end_alice = date_to_day_number(leaveAlice)
        start_bob = date_to_day_number(arriveBob)
        end_bob = date_to_day_number(leaveBob)
        
        # Find overlap
        overlap_start = max(start_alice, start_bob)
        overlap_end = min(end_alice, end_bob)
        
        if overlap_start <= overlap_end:
            return overlap_end - overlap_start + 1
        return 0