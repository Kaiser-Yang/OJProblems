// problem statement: https://leetcode.cn/problems/find-the-count-of-monotonic-pairs-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1e9 + 7;

public:
    int countOfPairs(vector<int> &nums) {
        int n = nums.size(), max_value = *max_element(nums.begin(), nums.end());
        vector<vector<int>> dp(n, vector<int>(max_value + 1));
        for (int j = 0; j <= nums[0]; j++) { dp[0][j] = 1; }
        for (int i = 1; i < n; i++) {
            vector<int> pre_sum(nums[i] + 1);
            pre_sum[0] = dp[i - 1][0];
            for (int j = 1; j <= nums[i]; j++) {
                pre_sum[j] = (pre_sum[j - 1] + dp[i - 1][j]) % MOD;
            }
            for (int j = 0; j <= nums[i]; j++) {
                if (nums[i - 1] - nums[i] + j < 0) { continue; }
                dp[i][j] = pre_sum[min(j, nums[i - 1] - nums[i] + j)];
            }
        }
        return accumulate(
            dp[n - 1].begin(), dp[n - 1].end(), 0, [](int a, int b) { return (a + b) % MOD; });
    }
};
