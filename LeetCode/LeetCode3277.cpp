// problem statement: https://leetcode.cn/problems/maximum-xor-score-subarray-queries/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int> &nums, vector<vector<int>> &queries) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0)), res(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) { dp[i][i] = nums[i]; res[i][i] = nums[i]; }
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                dp[l][r] = dp[l][r - 1] ^ dp[l + 1][r];
                res[l][r] = max({dp[l][r], res[l + 1][r], res[l][r - 1]});
            }
        }
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) { ans[i] = res[queries[i][0]][queries[i][1]]; }
        return ans;
    }
};
