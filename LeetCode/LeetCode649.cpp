// problem statement: https://leetcode.cn/problems/dota2-senate/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
    int getID(char ch) { return ch == 'R' ? 0 : 1; }
public:
    string predictPartyVictory(string senate) {
        queue<int> q[2], votedQ[2];
        for (int i = 0; i < senate.length(); i++) {
            q[getID(senate[i])].push(i);
        }
        while (true) {
            while (!q[0].empty() || !q[1].empty()) {
                if (q[0].empty()) {
                    if (votedQ[0].empty()) { return "Dire"; }
                    votedQ[0].pop();
                    votedQ[1].push(q[1].front());
                    q[1].pop();
                } else if (q[1].empty()) {
                    if (votedQ[1].empty()) { return "Radiant"; }
                    votedQ[1].pop();
                    votedQ[0].push(q[0].front());
                    q[0].pop();
                } else if (q[0].front() < q[1].front()) {
                    votedQ[0].push(q[0].front());
                    q[0].pop();
                    q[1].pop();
                } else {
                    votedQ[1].push(q[1].front());
                    q[1].pop();
                    q[0].pop();
                }
            }
            q[0].swap(votedQ[0]);
            q[1].swap(votedQ[1]);
        }
    }
};
