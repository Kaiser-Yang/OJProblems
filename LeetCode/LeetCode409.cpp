// problem statement: https://leetcode.cn/problems/longest-palindrome/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<int, int> cnt;
        for (int i = 0; i < s.length(); i++) { cnt[s[i]]++; }
        int ans = 0;
        for (auto &&item : cnt) { ans += item.second / 2; }
        ans *= 2;
        if (ans < s.length()) { ans++; }
        return ans;
    }
};
