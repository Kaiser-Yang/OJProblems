// problem statement: https://leetcode.cn/problems/maximize-score-of-numbers-in-ranges/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxPossibleScore(vector<int> &start, int d) {
        sort(start.begin(), start.end());
        int l = 0, r = start.back() + d;
        auto check = [&](int x) {
            int last = start[0];
            for (int i = 1; i < start.size(); i++) {
                if (start[i] + d - last < x) { return false; }
                last = max(last + x, start[i]);
            }
            return true;
        };
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return l - 1;
    }
};
