// problem statement:

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [] (const auto &a, const auto &b) {
            if (a[1] != b[1]) { return a[1] < b[1]; }
            return a[0] < b[0];
        });
        int ans = 1, nowRight = pairs[0][1];
        for (int i = 1; i < pairs.size(); i++) {
            if (pairs[i][0] > nowRight) {
                nowRight = pairs[i][1];
                ans++;
            }
        }
        return ans;
    }
};
