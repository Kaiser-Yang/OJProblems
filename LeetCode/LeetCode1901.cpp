// problem statement: https://leetcode.cn/problems/find-a-peak-element-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int check(vector<vector<int>> &mat, int i, int j) {
        if (i - 1 >= 0 && mat[i][j] < mat[i - 1][j]) { return -1; }
        if (i + 1 < mat.size() && mat[i][j] < mat[i + 1][j]) { return 1; }
        return 0;
    }

public:
    vector<int> findPeakGrid(vector<vector<int>> &mat) {
        int l = 0, r = mat.size() - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int p = -1, val = -1;
            for (int j = 0; j < mat[mid].size(); j++) {
                if (p == -1 || val < mat[mid][j]) {
                    p = j;
                    val = mat[mid][j];
                }
            }
            int ret = check(mat, mid, p);
            if (ret == 0) {
                return {mid, p};
            } else if (ret < 0) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return {};
    }
};