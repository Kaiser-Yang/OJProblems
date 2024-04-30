// problem statement: https://leetcode.cn/problems/rabbits-in-forest/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numRabbits(vector<int>& answers) {
        int ans = 0;
        map<int, int> cnt;
        for (int ans : answers) { cnt[ans]++; }
        for (auto &item : cnt) {
            while (item.second > 0) {
                ans += item.first + 1;
                item.second -= item.first + 1;
            }
        }
        return ans;
    }
};
