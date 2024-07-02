// problem statement: https://leetcode.cn/problems/ipo/description/

#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
        int n = profits.size();
        vector<pair<int, int>> twoCombination(n);
        for (int i = 0; i < n; i++) { twoCombination[i] = {profits[i], capital[i]}; }
        sort(twoCombination.begin(),
             twoCombination.end(),
             [&capital](const auto &a, const auto &b) { return a.second < b.second; });
        priority_queue<int> q;
        int i = 0;
        while (i < n) {
            if (twoCombination[i].second <= w) {
                q.push(twoCombination[i].first);
                i++;
                continue;
            }
            if (!q.empty() && k > 0) {
                k--;
                w += q.top();
                q.pop();
            } else {
                break;
            }
        }
        while (!q.empty() && k > 0) {
            k--;
            w += q.top();
            q.pop();
        }
        return w;
    }
};
