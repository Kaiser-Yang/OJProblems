// problem statement: https://leetcode.cn/problems/number-of-subarrays-with-and-value-of-k

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int> &nums, int k) {
        int n = nums.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i - 1; j >= 0 && (nums[j] & nums[i]) != nums[j]; j--) {
                nums[j] &= nums[i];
            }
            ans += upper_bound(nums.begin(), nums.begin() + i + 1, k) -
                   lower_bound(nums.begin(), nums.begin() + i + 1, k);
        }
        return ans;
    }
};
