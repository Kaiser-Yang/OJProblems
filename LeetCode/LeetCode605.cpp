// problem statement: https://leetcode.cn/problems/can-place-flowers/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int cnt = 0;
        for (int i = 0; i < flowerbed.size(); i++) {
            if (flowerbed[i]) { continue; }
            if ((i - 1 >= 0 && flowerbed[i - 1]) ||
                (i + 1 < flowerbed.size() && flowerbed[i + 1])) { continue; }
            flowerbed[i] = true;
            cnt++;
        }
        return cnt >= n;
    }
};
