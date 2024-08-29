// problem statement: https://leetcode.cn/problems/final-array-state-after-k-multiplication-operations-ii/

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

class Solution {
private:
    constexpr static int MOD = 1e9 + 7;

    int quick_pow(int a, long long b) {
        int res = 1;
        while (b) {
            if (b & 1) { res = 1LL * res * a % MOD; }
            a = 1LL * a * a % MOD;
            b >>= 1;
        }
        return res;
    }

public:
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
        if (multiplier == 1) { return nums; }
        long long max_value = *max_element(nums.begin(), nums.end());
        vector<pair<long long, int>> tmp;
        for (int i = 0; i < nums.size(); i++) { tmp.emplace_back(nums[i], i); }
        make_heap(tmp.begin(), tmp.end(), greater<pair<long long, int>>());
        while (k > 0 && tmp.front().first < max_value) {
            pop_heap(tmp.begin(), tmp.end(), greater<pair<long long, int>>());
            tmp.back().first *= multiplier;
            k--;
            push_heap(tmp.begin(), tmp.end(), greater<pair<long long, int>>());
        }
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < tmp.size(); i++) {
            tmp[i].first = tmp[i].first % MOD * quick_pow(multiplier, k / tmp.size() + (i < k % tmp.size())) % MOD;
        }
        for (int i = 0; i < tmp.size(); i++) { nums[tmp[i].second] = tmp[i].first; }
        return nums;
    }
};
