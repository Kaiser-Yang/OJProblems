// problem statement: https://leetcode.cn/problems/reach-end-of-array-with-max-score/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        vector<pair<int, int>> res;
        res.push_back({nums[0], 0});
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > res.back().first) { res.push_back({nums[i], i}); }
        }
        auto last = res[0];
        long long ans = 0;
        if (res.back().second != nums.size() - 1) { res.push_back({0, nums.size() - 1}); }
        for (int i = 1; i < res.size(); i++) {
            ans += 1LL * last.first * (res[i].second - last.second);
            last = res[i];
        }
        return ans;
    }
};
