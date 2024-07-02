// problem statement: https://leetcode.cn/problems/minimum-cost-to-hire-k-workers/

#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k) {
        vector<pair<int, int>> qAndW;
        for (int i = 0; i < quality.size(); i++) { qAndW.push_back({quality[i], wage[i]}); }
        auto &&cmp = [](const auto &a, const auto &b) {
            return a.second * b.first >= b.second * a.first;
        };
        sort(qAndW.begin(), qAndW.end(), cmp);
        double ans = numeric_limits<double>::max(), nowSumQ = 0;
        // minQSet stores the smallest k - 1 qualities
        // otherQ stores the other qualities
        multiset<int> minQSet, otherQ;
        for (int i = 1; i < qAndW.size(); i++) {
            if (minQSet.size() < k - 1) {
                nowSumQ += qAndW[i].first;
                minQSet.insert(qAndW[i].first);
            } else if (minQSet.empty() || *minQSet.rbegin() <= qAndW[i].first) {
                otherQ.insert(qAndW[i].first);
            } else {
                otherQ.insert(*minQSet.rbegin());
                nowSumQ -= *minQSet.rbegin();
                minQSet.erase(--minQSet.end());
                nowSumQ += qAndW[i].first;
                minQSet.insert(qAndW[i].first);
            }
        }
        int left = 0;
        while (left + k <= qAndW.size()) {
            ans = min(ans, nowSumQ / qAndW[left].first * qAndW[left].second + qAndW[left].second);
            left++;
            if (left + k > qAndW.size()) { break; }
            auto &&iter = minQSet.find(qAndW[left].first);
            if (iter != minQSet.end()) {
                nowSumQ -= qAndW[left].first;
                minQSet.erase(iter);
                nowSumQ += *otherQ.begin();
                minQSet.insert(*otherQ.begin());
                otherQ.erase(otherQ.begin());
            } else {
                otherQ.erase(otherQ.find(qAndW[left].first));
            }
        }
        return ans;
    }
};
