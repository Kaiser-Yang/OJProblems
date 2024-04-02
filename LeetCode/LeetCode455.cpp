// problem statement: https://leetcode.cn/problems/assign-cookies/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int ans = 0;
        int i = 0, j = 0;
        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i]) {
                ans++;
                i++;
                j++;
            }
            else { j++; }
        }
        return ans;
    }
};
