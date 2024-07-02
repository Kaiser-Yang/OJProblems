// problem statement: https://leetcode.cn/problems/max-chunks-to-make-sorted/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int> &arr) {
        int ans = 0, rightestPos = -1;
        for (int i = 0; i < (int)arr.size(); i++) {
            rightestPos = max(rightestPos, arr[i]);
            if (rightestPos == i) { ans++; }
        }
        return ans;
    }
};
