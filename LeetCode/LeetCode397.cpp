// problem statement: https://leetcode.cn/problems/integer-replacement/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int integerReplacement(int n) {
        int ans = 0;
        while (n != 1) {
            if (n & 1) {
                if (n % 4 == 1 || n == 3) {
                    n /= 2;
                } else {
                    n = n / 2 + 1;
                }
                ans += 2;
                continue;
            } else {
                n /= 2;
            }
            ans++;
        }
        return ans;
    }
};
