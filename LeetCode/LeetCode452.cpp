// problem statement:
// https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>> &points) {
        auto &&cmp = [](const auto &a, const auto &b) { return a[1] < b[1]; };
        sort(points.begin(), points.end(), cmp);
        int ans = 1, nowRight = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] <= nowRight) { continue; }
            nowRight = points[i][1];
            ans++;
        }
        return ans;
    }
};
