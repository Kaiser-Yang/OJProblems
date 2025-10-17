// problem statement: https://leetcode.cn/problems/nth-magical-number/description/

#include <vector>
class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long long l = lcm(a, b);
        long long cnt = l / a + l / b - 1;
        long long q = n / cnt;
        long long r = n % cnt;
        long long ans = q * l % MOD;
        std::vector<long long> candidates;
        for (int i = 0; i < r; i++) {
            candidates.push_back(1LL * (i + 1) * a);
            candidates.push_back(1LL * (i + 1) * b);
        }
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        if (r != 0) { ans = (ans + candidates[r - 1]) % MOD; }
        return ans;
    }

private:
    int lcm(int a, int b) { return a / gcd(a, b) * b; }

    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    static constexpr int MOD = 1e9 + 7;
};
