// problem statement: https://leetcode.cn/problems/maximum-score-from-grid-operations/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maximumScore(vector<vector<int>> &grid) {
        int n = grid.size();
        vector<vector<long long>> col_sum(n, vector<long long>(n + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { col_sum[i][j + 1] = col_sum[i][j] + grid[j][i]; }
        }
        vector<vector<vector<long long>>> dp(
            n, vector<vector<long long>>(n + 1, vector<long long>(2, 0)));
        for (int j = 0; j < n - 1; j++) {
            for (int nex = 0; nex <= n; nex++) {
                for (int desc = 0; desc < 2; desc++) {
                    auto &res = dp[j + 1][nex][desc];
                    for (int cur = 0; cur <= n; cur++) {
                        if (cur == nex) {
                            res = max(res, dp[j][cur][0]);
                        } else if (cur < nex) {
                            res = max(res, dp[j][cur][1] + col_sum[j][nex] - col_sum[j][cur]);
                        } else if (desc == 0) {
                            res =
                                max(res, dp[j][cur][0] + col_sum[j + 1][cur] - col_sum[j + 1][nex]);
                        } else if (nex == 0) {
                            res = max(res, dp[j][cur][0]);
                        }
                    }
                }
            }
        }
        long long ans = 0;
        for (auto &row : dp[n - 1]) { ans = max(ans, row[0]); }
        return ans;
    }
};
