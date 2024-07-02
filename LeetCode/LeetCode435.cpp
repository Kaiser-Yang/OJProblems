// problem statement: https://leetcode.cn/problems/non-overlapping-intervals/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        auto &&cmp = [](const auto &a, const auto &b) {
            if (a[1] != b[1]) { return a[1] < b[1]; }
            return a[0] > b[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        int nowRight = numeric_limits<int>::min(), ans = 0;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i][0] >= nowRight) {
                nowRight = max(nowRight, intervals[i][1]);
                continue;
            }
            ans++;
        }
        return ans;
    }
};
