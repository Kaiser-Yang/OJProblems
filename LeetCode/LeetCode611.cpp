// problem statement:

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            int j = i + 1, k = j;
            while (j + 1 < nums.size()) {
                if (k < j) { k = j; }
                while (k + 1 < nums.size() && nums[i] + nums[j] > nums[k + 1]) {
                    k++;
                }
                ans += k - j;
                j++;
            }
        }
        return ans;
    }
};
