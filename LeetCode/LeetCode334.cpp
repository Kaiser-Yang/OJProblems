// problem statement: https://leetcode.cn/problems/increasing-triplet-subsequence/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int> &nums) {
        int minVal = nums[0], subMinVal = numeric_limits<int>::max();
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > subMinVal) {
                return true;
            } else if (nums[i] > minVal) {
                subMinVal = nums[i];
            } else {
                minVal = nums[i];
            }
        }
        return false;
    }
};
