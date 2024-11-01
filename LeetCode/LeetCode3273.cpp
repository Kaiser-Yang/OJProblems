// problem statement:
// https://leetcode.cn/problems/minimum-amount-of-damage-dealt-to-bob/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minDamage(int power, vector<int> &damage, vector<int> &health) {
        int n = damage.size();
        vector<pair<int, int>> enemy_vec(n);
        for (int i = 0; i < n; i++) { enemy_vec[i] = make_pair(damage[i], health[i]); }
        sort(enemy_vec.begin(), enemy_vec.end(), [power](const auto &a, const auto &b) {
            return (a.second + power - 1) / power * b.first <
                   (b.second + power - 1) / power * a.first;
        });
        long long sum = accumulate(damage.begin(), damage.end(), 0LL);
        long long ans = 0;
        for (auto &&[d, h] : enemy_vec) {
            ans += sum * ((h + power - 1) / power);
            sum -= d;
        }
        return ans;
    }
};
