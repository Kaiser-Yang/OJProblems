// problem statement: https://leetcode.cn/problems/maximum-energy-boost-from-two-drinks/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        vector<long long> dp[2] = {vector<long long>(n, 0), vector<long long>(n, 0)};
        dp[0][0] = energyDrinkA[0];
        dp[1][0] = energyDrinkB[0];
        for (int i = 1; i < n; i++) {
            dp[0][i] = max(dp[1][i - 1], dp[0][i - 1] + energyDrinkA[i]);
            dp[1][i] = max(dp[0][i - 1], dp[1][i - 1] + energyDrinkB[i]);
        }
        return max(dp[0][n - 1], dp[1][n - 1]);
    }
};
