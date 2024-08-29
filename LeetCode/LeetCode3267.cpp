// problem statement: https://leetcode.cn/problems/count-almost-equal-pairs-ii/description/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countPairs(vector<int> &nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size(), ans = 0;

        unordered_set<string> res;
        unordered_map<int, int> cnt;

        for (int i = 0; i < n; i++) {
            res.insert(to_string(nums[i]));
            string num_str = to_string(nums[i]);
            int len = num_str.length();
            for (int a = 0; a < len; a++) {
                for (int b = a + 1; b < len; b++) {
                    swap(num_str[a], num_str[b]);
                    res.insert(num_str);
                    for (int c = 0; c < len; c++) {
                        for (int d = c + 1; d < len; d++) {
                            swap(num_str[c], num_str[d]);
                            res.insert(num_str);
                            swap(num_str[c], num_str[d]);
                        }
                    }
                    swap(num_str[a], num_str[b]);
                }
            }
            for (auto &&changed_num : res) { ans += cnt[stoi(changed_num)]; }
            cnt[nums[i]]++;
            res.clear();
        }
        return ans;
    }
};
