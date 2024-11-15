// problem statement:
// https://leetcode.cn/problems/minimum-length-of-string-after-operations/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        vector<int> cnt(26);
        for (int i = 0; i < s.size(); i++) { cnt[s[i] - 'a']++; }
        int ans = 0;
        for (int c : cnt) {
            if (c == 0) { continue; }
            if (c % 2 == 0) {
                ans += 2;
            } else {
                ans += 1;
            }
        }
        return ans;
    }
};
