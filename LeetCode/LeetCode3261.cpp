// problem statement: https://leetcode.cn/problems/super-egg-drop/description/

#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>> &queries) {
        int n = s.length();
        vector<int> farthest(n);
        vector<long long> pre_sum(n + 1);
        int cnt = 0, l = 0, r = -1;
        while (l < n) {
            while (r + 1 < n &&
                   (cnt + s[r + 1] - '0' <= k || r + 1 - l + 1 - cnt - (s[r + 1] - '0') <= k)) {
                r++;
                if (s[r] == '1') { cnt++; }
            }
            farthest[l] = r;
            if (s[l] == '1') { cnt--; }
            l++;
        }
        for (int i = 0; i < n; i++) { pre_sum[i + 1] = pre_sum[i] + farthest[i] - i + 1; }
        for (int i = 0; i < n; i++) { cout << farthest[i] << " "; }
        cout << endl;
        for (int i = 0; i < n + 1; i++) { cout << pre_sum[i] << " "; }
        cout << endl;
        vector<long long> ans;
        for (int i = 0; i < queries.size(); i++) {
            int l = queries[i][0], r = queries[i][1];
            int p =
                lower_bound(farthest.begin() + l, farthest.begin() + r + 1, r) - farthest.begin();
            ans.push_back(1LL * (r - p + 1) * (r - p + 2) / 2 + pre_sum[p] - pre_sum[l]);
        }
        return ans;
    }
};
