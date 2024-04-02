// problem statement: https://leetcode.cn/problems/course-schedule-iii/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [] (const auto &a, const auto &b) {
            return a[1] < b[1];
        });
        priority_queue<int> q;
        int now = 0;
        for (int i = 0; i < courses.size(); i++) {
            if (now + courses[i][0] <= courses[i][1]) {
                now += courses[i][0];
                q.push(courses[i][0]);
                continue;
            }
            if (!q.empty() && q.top() > courses[i][0]) {
                now += courses[i][0] - q.top();
                q.push(courses[i][0]);
                q.pop();
            }
        }
        return q.size();
    }
};
