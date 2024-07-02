// problem statement: https://leetcode.cn/problems/minimum-number-of-refueling-stops/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
        priority_queue<pair<int, int>> q;
        int i = 0;
        for (auto &&item : stations) {
            assert(item.size() == 2);
            if (item[0] > startFuel) { break; }
            q.push({item[1], item[0]});
            i++;
        }
        int ans = 0, maxPos = startFuel;
        while (maxPos < target) {
            if (q.empty()) { return -1; }
            maxPos += q.top().first;
            q.pop();
            ans++;
            while (i < (int)stations.size()) {
                if (stations[i][0] > maxPos) { break; }
                q.push({stations[i][1], stations[i][0]});
                i++;
            }
        }
        return ans;
    }
};
