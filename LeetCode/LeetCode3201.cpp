// problem statement: https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-i/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int ans = 0, cnt = 0;
        for (auto &&num : nums) {
            if (num % 2 == 0) { ans++; }
            else { cnt++; }
        }
        ans = max(ans, cnt);
        int last = 0;
        cnt = 0;
        for (auto &&num : nums) {
            if (num % 2 == last) { continue; }
            last = num % 2;
            cnt++;
        }
        ans = max(ans, cnt);
        last = 1, cnt = 0;
        for (auto &&num : nums) {
            if (num % 2 == last) { continue; }
            last = num % 2;
            cnt++;
        }
        ans = max(ans, cnt);
        return ans;
    }
};
