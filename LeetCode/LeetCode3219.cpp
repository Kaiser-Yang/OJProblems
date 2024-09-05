// problem statement: https://leetcode.cn/problems/minimum-cost-for-cutting-cake-ii

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.begin(), horizontalCut.end());
        sort(verticalCut.begin(), verticalCut.end());
        long long ans = 0;
        int vertical_cut_cnt = 0, horizontal_cut_cnt = 0;
        while (!horizontalCut.empty() || !verticalCut.empty()) {
            if (verticalCut.empty()) {
                ans += 1LL * horizontalCut.back() * (vertical_cut_cnt + 1);
                horizontalCut.pop_back();
                horizontal_cut_cnt++;
            } else if (horizontalCut.empty()) {
                ans += 1LL * verticalCut.back() * (horizontal_cut_cnt + 1);
                verticalCut.pop_back();
                vertical_cut_cnt++;
            } else if (verticalCut.back() > horizontalCut.back()) {
                ans += 1LL * verticalCut.back() * (horizontal_cut_cnt + 1);
                verticalCut.pop_back();
                vertical_cut_cnt++;
            } else {
                ans += 1LL * horizontalCut.back() * (vertical_cut_cnt + 1);
                horizontalCut.pop_back();
                horizontal_cut_cnt++;
            }
        }
        return ans;
    }
};
