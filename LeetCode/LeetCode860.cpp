// problem statement: https://leetcode.cn/problems/lemonade-change/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int cnt1 = 0, cnt2 = 0, cnt3 = 0;
        for (int i = 0; i < bills.size(); i++) {
            if (bills[i] == 5) {
                cnt1++;
            } else if (bills[i] == 10) {
                if (cnt1 == 0) { return false; }
                cnt1--;
                cnt2++;
            } else {
                if (cnt1 >= 1 && cnt2 >= 1) {
                    cnt1--;
                    cnt2--;
                    cnt3++;
                } else if (cnt1 >= 3) {
                    cnt1 -= 3;
                    cnt3++;
                } else { 
                    return false;
                }
            }
        }
        return true;
    }
};
