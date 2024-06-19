// problem statement: https://leetcode.cn/problems/maximum-strictly-increasing-cells-in-a-matrix

#include <bits/stdc++.h>

using namespace std;

class Solution {
    struct State {
        int x, y, val;
        State(int x, int y, int val) : x(x), y(y), val(val) {}
        bool operator>(const State &s) const { return val > s.val; }
    };

public:
    int maxIncreasingCells(vector<vector<int>> &mat) {
        vector<State> a;
        a.emplace_back(0, 0, numeric_limits<int>::max());
        int n = mat.size(), m = mat[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) { a.emplace_back(i + 1, j + 1, mat[i][j]); }
        }
        sort(a.begin(), a.end(), greater<State>());
        int ans = 0, val1 = 0, val2 = 0;
        vector<int> dp(n * m + 1), maxRow(n + 1), maxColumn(m + 1), subMaxRow(n + 1),
            subMaxColumn(m + 1);
        for (int i = 1; i < a.size(); i++) {
            val1  = a[maxRow[a[i].x]].val == a[i].val ? dp[subMaxRow[a[i].x]] : dp[maxRow[a[i].x]];
            val2  = a[maxColumn[a[i].y]].val == a[i].val ? dp[subMaxColumn[a[i].y]] :
                                                           dp[maxColumn[a[i].y]];
            dp[i] = 1 + max(val1, val2);
            ans   = max(ans, dp[i]);
            if (dp[i] > dp[maxRow[a[i].x]]) {
                if (a[maxRow[a[i].x]].val != a[i].val) { subMaxRow[a[i].x] = maxRow[a[i].x]; }
                maxRow[a[i].x] = i;
            } else if (dp[i] > dp[subMaxRow[a[i].x]] && a[maxRow[a[i].x]].val != a[i].val) {
                subMaxRow[a[i].x] = i;
            }
            if (dp[i] > dp[maxColumn[a[i].y]]) {
                if (a[maxColumn[a[i].y]].val != a[i].val) {
                    subMaxColumn[a[i].y] = maxColumn[a[i].y];
                }
                maxColumn[a[i].y] = i;
            } else if (dp[i] > dp[subMaxColumn[a[i].y]] && a[maxColumn[a[i].y]].val != a[i].val) {
                subMaxColumn[a[i].y] = i;
            }
        }
        return ans;
    }
};
