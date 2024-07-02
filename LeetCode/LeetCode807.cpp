// problem statement: https://leetcode.cn/problems/max-increase-to-keep-city-skyline/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>> &grid) {
        int n = (int)grid.size();
        vector<int> maxColumn(n), maxRow(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                maxRow[i]    = max(maxRow[i], grid[i][j]);
                maxColumn[j] = max(maxColumn[j], grid[i][j]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { ans += min(maxRow[i], maxColumn[j]) - grid[i][j]; }
        }
        return ans;
    }
};
