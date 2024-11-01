// problem statement:
// https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>> &nums) {
        int k = nums.size();
        vector<int> p(k);
        int maxVal = numeric_limits<int>::min();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        for (int i = 0; i < k; i++) {
            if (nums[i][0] > maxVal) { maxVal = nums[i][0]; }
            q.push({nums[i][0], i});
        }
        int ansLeft = -1, ansRight = -1, minVal = -1, minPos = -1;
        while (true) {
            auto item = q.top();
            q.pop();
            minVal = item.first, minPos = item.second;
            if (ansLeft == -1 || ansRight - ansLeft > maxVal - minVal ||
                (ansRight - ansLeft == maxVal - minVal && ansLeft > minVal)) {
                ansLeft = minVal;
                ansRight = maxVal;
            }
            p[minPos]++;
            if (p[minPos] == nums[minPos].size()) { break; }
            maxVal = max(maxVal, nums[minPos][p[minPos]]);
            q.push({nums[minPos][p[minPos]], minPos});
        }
        return {ansLeft, ansRight};
    }
};
