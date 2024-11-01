// problem statement: https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int> &nums, int k) {
        int n = nums.size(), ans = 0;
        for (int rest = 0; rest < k; rest++) {
            vector<int> dp(k);
            for (int num : nums) {
                dp[num % k] = dp[(rest - num % k + k) % k] + 1;
                ans = max(ans, dp[num % k]);
            }
        }
        return ans;
    }
};
