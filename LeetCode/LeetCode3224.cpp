// problem statement: https://leetcode.cn/problems/minimum-array-changes-to-make-differences-equal/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> max_x(n / 2), cnt(k + 1);
        for (int i = 0; i < n / 2; i++) {
            max_x[i] = max(max(nums[i], nums[n - i - 1]), k - min(nums[i], nums[n - i - 1]));
            cnt[abs(nums[i] - nums[n - i - 1])]++;
        }
        sort(max_x.begin(), max_x.end());
        int ans = n / 2;
        for (int x = 0; x <= k; x++) {
            int l = lower_bound(max_x.begin(), max_x.end(), x) - max_x.begin();
            ans = min(ans, 2 * l + n / 2 - l - cnt[x]);
        }
        return ans;
    }
};
