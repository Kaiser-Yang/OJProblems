// problem statement: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int buyPrice = prices[0];
        int i = 0;
        while (i + 1 < prices.size()) {
            while (i + 1 < prices.size() && prices[i + 1] >= prices[i]) { i++; }
            ans += prices[i] - buyPrice;
            while (i + 1 < prices.size() && prices[i + 1] <= prices[i]) { i++; }
            buyPrice = prices[i];
        }
        return ans;
    }
};
