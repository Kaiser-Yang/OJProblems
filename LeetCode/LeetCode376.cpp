// problem statement: https://leetcode.cn/problems/wiggle-subsequence/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int> &nums) {
        vector<int> diff(nums.size() - 1);
        for (int i = 1; i < nums.size(); i++) { diff[i - 1] = nums[i] - nums[i - 1]; }
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < diff.size(); i++) {
            if ((cnt1 % 2 == 0 && diff[i] < 0) || (cnt1 % 2 == 1 && diff[i] > 0)) { cnt1++; }
            if ((cnt2 % 2 == 0 && diff[i] > 0) || (cnt2 % 2 == 1 && diff[i] < 0)) { cnt2++; }
        }
        return max(cnt1, cnt2) + 1;
    }
};
