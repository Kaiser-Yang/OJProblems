// problem statement: https://leetcode.cn/problems/minimum-jumps-to-reach-home/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumJumps(vector<int> &forbidden, int a, int b, int x) {
        int bound = x + b;
        for (int p : forbidden) { bound = max(bound, p + a + b); }
        vector<bool> reachable(bound + 1, true);
        for (int p : forbidden) { reachable[p] = false; }
        vector<vector<int>> dis;
        dis.resize(bound + 1);
        for (int i = 0; i <= bound; i++) { dis[i].resize(2, numeric_limits<int>::max() / 2); }
        queue<pair<int, int>> q;
        q.push({0, 0});
        dis[0][0] = 0;
        while (!q.empty()) {
            auto item = q.front();
            q.pop();
            int i = item.first, s = item.second;
            if (i == x) { return dis[i][s]; }
            if (s != 1 && i - b >= 0 && reachable[i - b] && dis[i - b][1] > dis[i][s] + 1) {
                dis[i - b][1] = dis[i][s] + 1;
                q.push({i - b, 1});
            }
            if (i + a <= bound && reachable[i + a] && dis[i + a][0] > dis[i][s] + 1) {
                dis[i + a][0] = dis[i][s] + 1;
                q.push({i + a, 0});
            }
        }
        return -1;
    }
};
