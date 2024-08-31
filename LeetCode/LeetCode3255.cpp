// problem statement: https://leetcode.cn/problems/find-the-power-of-k-size-subarrays-ii/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res, farthest(n);
        int l = 0, r = 0;
        while (r < n) {
            while (r + 1 < n && nums[r + 1] == nums[r] + 1) { r++; }
            farthest[l] = r;
            l = r = r + 1;
        }
        for (int i = 1; i < n; i++) {
            farthest[i] = max({i, farthest[i - 1], farthest[i]});
        }
        for (int i = 0; i + k - 1 < n; i++) {
            if (farthest[i] >= i + k - 1) {
                res.push_back(nums[i + k - 1]);
            } else {
                res.push_back(-1);
            }
        }
        return res;
    }
};
