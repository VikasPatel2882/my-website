#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        // Min-heap for free servers: {weight, index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> free_servers;
        for (int i = 0; i < n; ++i) {
            free_servers.push({servers[i], i});
        }
        
        // Min-heap for busy servers: {free_time, weight, index}
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> busy_servers;
        
        vector<int> ans(m);
        long long curr_time = 0;
        
        for (int j = 0; j < m; ++j) {
            curr_time = max(curr_time, (long long)j);
            
            // If no free servers are available, jump time to when the next server becomes free
            if (free_servers.empty()) {
                curr_time = get<0>(busy_servers.top());
            }
            
            // Release all servers that finish their tasks at or before curr_time
            while (!busy_servers.empty() && get<0>(busy_servers.top()) <= curr_time) {
                auto [free_time, w, idx] = busy_servers.top();
                busy_servers.pop();
                free_servers.push({w, idx});
            }
            
            // Assign current task to the best available free server
            auto [w, idx] = free_servers.top();
            free_servers.pop();
            
            ans[j] = idx;
            busy_servers.push({curr_time + tasks[j], w, idx});
        }
        
        return ans;
    }
};