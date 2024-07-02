// problem statement:
// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices, int fee) {
        vector<vector<int>> dp(2, vector<int>(2));
        int now = 0, las = 1;
        dp[las][0] = 0;
        dp[las][1] = numeric_limits<int>::min();
        for (int i = 0; i < prices.size(); i++) {
            dp[now][0] = max(dp[las][0], dp[las][1] + prices[i]);
            dp[now][1] = max(dp[las][1], dp[las][0] - prices[i] - fee);
            swap(now, las);
        }
        return max(dp[las][0], dp[las][1]);
    }
};
