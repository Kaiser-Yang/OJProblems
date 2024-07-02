// problem statement: https://leetcode.cn/problems/most-profit-assigning-work/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker) {
        using Work = pair<int, int>;
        vector<Work> workList;
        int n = (int)difficulty.size();
        for (int i = 0; i < n; i++) { workList.push_back({profit[i], difficulty[i]}); }
        auto comparor = [](const Work &a, const Work &b) {
            if (a.first != b.first) { return a.first > b.first; }
            return a.second < b.second;
        };
        sort(workList.begin(), workList.end(), comparor);
        sort(worker.begin(), worker.end(), greater<int>());
        int now = 0, ans = 0;
        for (int i = 0; i < (int)worker.size();) {
            if (worker[i] >= workList[now].second) {
                ans += workList[now].first;
                i++;
            } else {
                now++;
            }
            if (now == workList.size()) { break; }
        }
        return ans;
    }
};
