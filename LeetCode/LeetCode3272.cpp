// problem statement: https://leetcode.cn/problems/find-the-count-of-good-integers/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; i++) { f[i] = f[i - 1] * i; }
        long long ans = 0;
        unordered_set<string> s;
        int min_left_part = pow(10, (n - 1) / 2);
        for (int left_part = min_left_part; left_part < min_left_part * 10; left_part++) {
            string num = to_string(left_part);
            num += string(num.rbegin() + n % 2, num.rend());
            assert(n == num.length());
            if (stoll(num) % k != 0) { continue; }
            sort(num.begin(), num.end());
            if (!s.insert(num).second) { continue; }
            vector<int> cnt(10);
            for (auto &&ch : num) { cnt[ch - '0']++; }
            long long res = (n - cnt[0]) * f[n - 1];
            for (auto &&c : cnt) { res /= f[c]; }
            ans += res;
        }
        return ans;
    }
};
