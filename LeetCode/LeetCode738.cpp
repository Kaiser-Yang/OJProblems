// problem statement: https://leetcode.cn/problems/monotone-increasing-digits/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string num = to_string(n);
        int pos    = -1;
        for (int i = 0; i + 1 < num.length(); i++) {
            if (num[i] > num[i + 1]) {
                pos = i;
                break;
            }
        }
        if (pos == -1) { return stoi(num); }
        if (stoi(string(num.size(), '1')) > n) { return stoi(string(num.size() - 1, '9')); }
        string ans;
        for (int i = 0; i < num.length(); i++) {
            char ch    = num[i];
            char limit = '0';
            if (!ans.empty()) {
                limit = ans.back();
            } else if (num.length() == 1) {
                limit = '0';
            } else {
                limit = '1';
            }
            while (ch >= limit && stoi(ans + string(num.length() - i, ch)) > n) { ch--; }
            assert(ch >= limit);
            ans.push_back(ch);
            if (ch < num[i]) {
                ans += string(num.length() - ans.length(), '9');
                break;
            }
        }
        return stoi(ans);
    }
};
