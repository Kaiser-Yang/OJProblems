// problem statement: https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-i/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumArea(vector<vector<int>> &grid) {
        int l = numeric_limits<int>::max(), r = numeric_limits<int>::min(),
            u = numeric_limits<int>::max(), d = numeric_limits<int>::min();
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 0) { continue; }
                l = min(l, j);
                r = max(r, j);
                u = min(u, i);
                d = max(d, i);
            }
        }
        return (r - l + 1) * (d - u + 1);
    }
};
