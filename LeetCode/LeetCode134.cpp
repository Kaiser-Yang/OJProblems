// problem statement: https://leetcode.cn/problems/gas-station/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<int> difference(n * 2);
        int sum = 0;
        for (int i = 0; i < n; i++) { difference[i] = difference[i + n] = gas[i] - cost[i]; }
        int l = 0, r = 0;
        while (l < n) {
            while (sum + difference[r] >= 0 && l + n > r) { sum += difference[r++]; }
            if (r - l == n) { return l; }
            sum -= difference[l];
            l++;
        }
        return -1;
    }
};
