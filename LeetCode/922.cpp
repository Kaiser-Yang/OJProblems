// problem statement: https://leetcode.cn/problems/sort-array-by-parity-ii/

#include <vector>

class Solution {
public:
    std::vector<int> sortArrayByParityII(std::vector<int> &nums) {
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (((i % 2) ^ (nums[i] % 2)) == 0) { continue; }
            if (j <= i) { j = i + 1; }
            while (j < nums.size() && (nums[j] % 2) ^ (i % 2)) { j++; }
            std::swap(nums[i], nums[j]);
        }
        return nums;
    }
};
