// problem statement:
// https://leetcode.cn/problems/count-the-number-of-substrings-with-dominant-ones/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        deque<int> zero_pos;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') { zero_pos.push_back(i); }
        }
        zero_pos.push_back(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (!zero_pos.empty() && zero_pos.front() <= i) { zero_pos.pop_front(); }
            int cnt0 = (s[i] == '0' ? 1 : 0);
            int cnt1 = (s[i] == '1' ? 1 : 0);
            int last = i;
            int max_cnt0 = sqrt(n - i);
            if (cnt1 == 1) { ans++; }
            for (int j = 0; j < zero_pos.size() && cnt0 <= max_cnt0; j++) {
                cnt1 += zero_pos[j] - last - 1;
                ans += min(zero_pos[j] - last - 1, max(0, cnt1 - cnt0 * cnt0 + 1));
                last = zero_pos[j];
                cnt0++;
                if (cnt1 >= cnt0 * cnt0 && j != zero_pos.size() - 1) { ans++; }
            }
        }
        return ans;
    }
};
