// problem statement: https://leetcode.cn/problems/partition-labels/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> rightestPos;
        vector<int> ans;
        for (int i = 0; i < s.length(); i++) { rightestPos[s[i]] = i; }
        int i = 0;
        while (i < s.length()) {
            int right = rightestPos[i];
            for (int j = i; j <= right; j++) { right = max(right, rightestPos[j]); }
            ans.push_back(right - i + 1);
            i = right + 1;
        }
        return ans;
    }
};
