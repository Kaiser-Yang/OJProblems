// problem statement:
// https://leetcode.cn/problems/split-array-into-consecutive-subsequences/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isPossible(vector<int> &nums) {
        unordered_map<int, int> cnt1;
        unordered_map<int, int> cnt2;
        for (int num : nums) { cnt1[num]++; }
        for (int num : nums) {
            while (cnt1[num] > 0) {
                if (cnt2[num - 1] == 0) {
                    if (cnt1[num + 1] == 0 || cnt1[num + 2] == 0) { return false; }
                    cnt1[num]--;
                    cnt1[num + 1]--;
                    cnt1[num + 2]--;
                    cnt2[num + 2]++;
                } else {
                    cnt1[num]--;
                    cnt2[num - 1]--;
                    cnt2[num]++;
                }
            }
        }
        return true;
    }
};
