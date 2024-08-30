// problem statement:
// https://leetcode.cn/problems/maximum-value-sum-by-placing-three-rooks-ii/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maximumValueSum(vector<vector<int>> &board) {
        int n = board.size(), m = board[0].size();
        long long ans = numeric_limits<long long>::min();
        vector<vector<pair<int, int>>> before(
            n, vector<pair<int, int>>(3, {-1, numeric_limits<int>::min()})),
            after(n, vector<pair<int, int>>(3, {-1, numeric_limits<int>::min()}));
        auto update = [](auto &row, auto &res) {
            for (int i = 0; i < row.size(); i++) {
                if (row[i] > res[0].second) {
                    if (res[0].first != i) {
                        if (res[1].first != i) { res[2] = res[1]; }
                        res[1] = res[0];
                    }
                    res[0] = {i, row[i]};
                } else if (row[i] > res[1].second && i != res[0].first) {
                    if (res[1].first != i) { res[2] = res[1]; }
                    res[1] = {i, row[i]};
                } else if (row[i] > res[2].second && i != res[0].first && i != res[1].first) {
                    res[2] = {i, row[i]};
                }
            }
        };
        for (int i = 1; i < n - 1; i++) {
            before[i] = before[i - 1];
            update(board[i - 1], before[i]);
        }
        for (int i = n - 2; i >= 1; i--) {
            after[i] = after[i + 1];
            update(board[i + 1], after[i]);
        }
        for (int j = 1; j < n - 1; j++) {
            for (int b = 0; b < m; b++) {
                for (auto &[a, val1] : before[j]) {
                    for (auto &[c, val2] : after[j]) {
                        if (a != b && b != c && a != c) {
                            ans = max(ans, (long long)val1 + board[j][b] + val2);
                        }
                    }
                }
            }
        }
        return ans;
    }
};

