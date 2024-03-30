// problem statement: https://leetcode.cn/problems/patching-array/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int ans = 0;
        long long unreachableNum = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (unreachableNum - 1 >= n) { break; }
            if (nums[i] == unreachableNum) { unreachableNum <<= 1; }
            else if (nums[i] < unreachableNum) { unreachableNum += nums[i]; }
            else {
                ans++;
                unreachableNum <<= 1;
                i--;
            }
        }
        while (unreachableNum - 1 < n) {
            ans++;
            unreachableNum <<= 1;
        }
        return ans;
    }
};
