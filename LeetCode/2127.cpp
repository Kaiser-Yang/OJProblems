// problem statement:
// https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/description/

#include <queue>
#include <vector>

class Solution {
public:
    int maximumInvitations(std::vector<int> &favorite) {
        std::vector<int> in_degree(favorite.size()), dp(favorite.size());
        for (int i = 0; i < favorite.size(); i++) { in_degree[favorite[i]]++; }
        auto topo_sort = [&]() {
            std::queue<int> q;
            for (int i = 0; i < favorite.size(); i++) {
                if (in_degree[i] == 0) { q.push(i); }
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                int v = favorite[u];
                in_degree[v]--;
                dp[v] = std::max(dp[v], dp[u] + 1);
                if (in_degree[v] == 0) { q.push(v); }
            }
        };
        topo_sort();
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < favorite.size(); i++) {
            if (in_degree[i] == 0) { continue; }
            int cnt = 0;
            for (int u = i; in_degree[u] > 0; u = favorite[u]) {
                in_degree[u] = 0;
                cnt++;
            }
            if (cnt == 2) {
                ans1 += dp[i] + dp[favorite[i]] + 2;

            } else {
                ans2 = std::max(ans2, cnt);
            }
        }
        return std::max(ans1, ans2);
    }
};
