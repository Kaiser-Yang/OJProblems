// problem statement: https://leetcode.cn/problems/reverse-pairs/

#include <vector>

using namespace std;

class Solution {
public:
    int reversePairs(vector<int> &nums) { return solve(nums, 0, nums.size()); }

private:
    int solve(vector<int> &nums, size_t l, size_t r) {
        if (r - l <= 1) { return 0; }
        size_t m = (l + r) / 2;
        int res = solve(nums, l, m) + solve(nums, m, r);
        vector<int> temp(r - l);
        int i = l, j = m, k = 0;
        while (i < m && j < r) {
            if (nums[i] > 2LL * nums[j]) {
                res += m - i;
                j++;
            } else {
                i++;
            }
        }
        i = l, j = m, k = 0;
        while (i < m || j < r) {
            if (j == r || (i < m && nums[i] <= nums[j])) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }
        for (size_t i = l; i < r; i++) { nums[i] = temp[i - l]; }
        return res;
    }
};
