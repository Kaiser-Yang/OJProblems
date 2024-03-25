// problem statement: https://leetcode.cn/problems/largest-number/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [] (const auto &a, const auto &b) {
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        });
        string ans = "";
        for (auto &&num : nums) { ans += to_string(num); }
        reverse(ans.begin(), ans.end());
        while (ans.size() > 1 && ans.back() == '0') { ans.pop_back(); }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
