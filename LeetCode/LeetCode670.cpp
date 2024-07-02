// problem statement: https://leetcode.cn/problems/maximum-swap/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        string s   = to_string(num);
        int maxIdx = -1, left = -1, right = -1;
        ;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (maxIdx == -1 || s[i] > s[maxIdx]) {
                maxIdx = i;
            } else if (s[i] < s[maxIdx]) {
                left = i, right = maxIdx;
            }
        }
        if (left != -1) { swap(s[left], s[right]); }
        return stoi(s);
    }
};
