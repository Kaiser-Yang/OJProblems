// problem statement: https://leetcode.cn/problems/minimum-operations-to-make-array-equal-to-target/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        long long ans = abs(nums[0] - target[0]);
        long long increment = target[0] - nums[0];
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            long long cnt = (target[i] - target[i - 1]) - (nums[i] - nums[i - 1]);
            if (cnt == 0) { continue; }
            else if (cnt > 0) {
                ans += (increment < 0 ? max(0LL, increment + cnt) : cnt);
            } else {
                ans += (increment > 0 ? -min(0LL, increment + cnt) : -cnt);
            }
            increment += cnt;
        }
        return ans;
    }
};
