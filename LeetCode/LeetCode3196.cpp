// problem statement: https://leetcode.cn/problems/maximize-total-cost-of-alternating-subarrays/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maximumTotalCost(vector<int> &nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2));
        dp[0][0] = nums[0];
        dp[0][1] = std::numeric_limits<long long>::min();
        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i];
            dp[i][1] = dp[i - 1][0] - nums[i];
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
