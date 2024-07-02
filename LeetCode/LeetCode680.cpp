// problem statement: https://leetcode.cn/problems/valid-palindrome-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    bool check(string s, int pos) {
        s.erase(pos, 1);
        int n = s.length();
        for (int i = 0; i < n; i++) {
            if (s[i] != s[n - 1 - i]) { return false; }
        }
        return true;
    }

public:
    bool validPalindrome(string s) {
        int n = s.length(), pos = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == s[n - 1 - i]) { continue; }
            pos = i;
            break;
        }
        if (pos == -1) { return true; }
        return check(s, pos) || check(s, n - 1 - pos);
    }
};
