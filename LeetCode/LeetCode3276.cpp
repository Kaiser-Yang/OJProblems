// problem statement: https://leetcode.cn/problems/select-cells-in-grid-with-maximum-score/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>> &grid) {
        map<int, int, greater<int>> pos;
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (auto &&val : grid[i]) { pos[val] |= (1 << i); }
        }
        vector<int> all_num;
        for (auto &&[val, _] : pos) { all_num.push_back(val); }
        vector<vector<int>> dp(all_num.size() + 1, vector<int>(1 << n, 0));
        int ans = 0;
        for (int i = 0; i < all_num.size(); i++) {
            int now = all_num[i];
            for (int state = 0; state < (1 << n); state++) {
                dp[i + 1][state] = max(dp[i + 1][state], dp[i][state]);
                for (int t = pos[now]; t > 0; t -= t & (-t)) {
                    if ((state & (t & (-t))) == 0) {
                        int new_state = state | (t & (-t));
                        dp[i + 1][new_state] = max(dp[i + 1][new_state], dp[i][state] + now);
                        ans = max(ans, dp[i + 1][new_state]);
                    }
                }
            }
        }
        return ans;
    }
};
