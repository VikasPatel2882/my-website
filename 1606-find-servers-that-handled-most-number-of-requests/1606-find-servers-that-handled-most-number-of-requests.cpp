#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;
        set<int> available;
        
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        vector<int> request_count(k, 0);
        
        for (int i = 0; i < n; ++i) {
            long long t = arrival[i];
            long long l = load[i];
            
            while (!busy.empty() && busy.top().first <= t) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            if (available.empty()) {
                continue;
            }
            
            auto it = available.lower_bound(i % k);
            if (it == available.end()) {
                it = available.begin();
            }
            
            int assigned_server = *it;
            available.erase(it);
            
            request_count[assigned_server]++;
            busy.push({t + l, assigned_server});
        }
        
        int max_reqs = *max_element(request_count.begin(), request_count.end());
        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            if (request_count[i] == max_reqs) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};