// problem statement: https://leetcode.cn/problems/maximum-points-after-enemy-battles/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maximumPoints(vector<int> &enemyEnergies, int currentEnergy) {
        sort(enemyEnergies.begin(), enemyEnergies.end());
        long long ans = 0;
        long long sum = accumulate(enemyEnergies.begin(), enemyEnergies.end(), 0LL);
        sum -= enemyEnergies[0];
        if (currentEnergy >= enemyEnergies[0]) { ans += (sum + currentEnergy) / enemyEnergies[0]; }
        return ans;
    }
};
