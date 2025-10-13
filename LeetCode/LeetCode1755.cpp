// problem statement: https://leetcode.cn/problems/closest-subsequence-sum

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minAbsDifference(vector<int> &nums, int goal) {
        vector<int> left, right;
        for (int i = 0; i < nums.size() / 2; i++) { left.push_back(nums[i]); }
        for (int i = nums.size() / 2; i < nums.size(); i++) { right.push_back(nums[i]); }
        vector<int> sum;
        for (int s = 0; s < (1 << left.size()); s++) {
            int cur = 0;
            for (int i = 0; i < left.size(); i++) {
                if (s & (1 << i)) { cur += left[i]; }
            }
            sum.push_back(cur);
        }
        sort(sum.begin(), sum.end());
        sum.erase(unique(sum.begin(), sum.end()), sum.end());
        int ans = abs(goal);
        for (int s = 0; s < (1 << right.size()); s++) {
            int cur = 0;
            for (int i = 0; i < right.size(); i++) {
                if (s & (1 << i)) { cur += right[i]; }
            }
            int target = goal - cur;
            auto lower = lower_bound(sum.begin(), sum.end(), target);
            auto upper = upper_bound(sum.begin(), sum.end(), target);
            if (lower == upper && lower != sum.begin()) { lower--; }
            if (lower != sum.end() && abs(*lower + cur - goal) < ans) {
                ans = abs(*lower + cur - goal);
            }
            if (upper != sum.end() && abs(*upper + cur - goal) < ans) {
                ans = abs(*upper + cur - goal);
            }
        }
        return ans;
    }
};
