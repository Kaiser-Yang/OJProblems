// problem statement: https://leetcode.cn/problems/split-array-largest-sum/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    bool check(const vector<int>& nums, int k, int ans)
    {
        if (nums[0] > ans) { return false; }
        int nowSum = nums[0], nowCnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nowSum + nums[i] <= ans) { nowSum += nums[i]; }
            else if (nums[i] <= ans) {
                nowSum = nums[i];
                nowCnt++;
            }
            else { return false; }
        }
        return nowCnt <= k;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        int l = 0, r = accumulate(nums.begin(), nums.end(), 0);
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(nums, k, mid)) { r = mid - 1; }
            else { l = mid + 1; }
        }
        return l;
    }
};
