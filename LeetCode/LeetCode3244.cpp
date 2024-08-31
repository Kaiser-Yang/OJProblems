// problem statement:
// https://leetcode.cn/problems/shortest-distance-after-road-addition-queries-ii/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>> &queries) {
        set<pair<int, int>> s;
        vector<int> res;
        for (int i = 0; i < n - 1; i++) { s.insert({i, i + 1}); }
        for (auto &&item : queries) {
            int l = item[0], r = item[1];
            auto p1 = s.upper_bound({l, n});
            p1--;
            auto p2 = s.upper_bound({r, n});
            if (p1->second >= r) {
                res.push_back(s.size());
                continue;
            }
            pair<int, int> new_val1 = {p1->first, l}, new_val2 = {l, r},
                           new_val3 = {r, p2 == s.end() ? n - 1 : p2->first};
            s.erase(p1, p2);
            if (new_val1.first != new_val1.second) { s.insert(new_val1); }
            s.insert(new_val2);
            if (new_val3.first != new_val3.second) { s.insert(new_val3); }
            res.push_back(s.size());
        }
        return res;
    }
};
