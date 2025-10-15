#include <cstdint>
#include <iostream>
#include <vector>

using u64 = uint64_t;
using i64 = int64_t;

class linear_sieve {
public:
    // return the mobius function of [1, n)
    static std::vector<int> mobius(int n) {
        std::vector<int> res(n, 1);
        std::vector<int> primes;
        std::vector<bool> is_composite(n, false);
        for (int i = 2; i < n; i++) {
            if (!is_composite[i]) {
                primes.push_back(i);
                res[i] = -1;
            }
            for (int p : primes) {
                if ((long long)p * i >= n) { break; }
                is_composite[p * i] = true;
                if (i % p == 0) {
                    res[p * i] = 0;
                    break;
                }
                res[p * i] = -res[i];
            }
        }
        return res;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int max_a = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        max_a = std::max(max_a, a[i]);
    }
    constexpr i64 MOD = 1e9 + 7;
    auto quick_pow = [&](u64 a, int b) {
        i64 res = 1 % MOD;
        a %= MOD;
        while (b) {
            if (b & 1) { res = (u64)res * a % MOD; }
            a = (u64)a * a % MOD;
            b >>= 1;
        }
        return res;
    };
    std::vector<int> cnt(max_a + 1), freq(max_a + 1);
    for (int i = 0; i < n; i++) { freq[a[i]]++; }
    for (int i = 1; i <= max_a; i++) {
        for (int j = i; j <= max_a; j += i) { cnt[i] += freq[j]; }
    }
    i64 ans = 0;
    auto mobius = linear_sieve::mobius(max_a + 1);
    for (int i = 1; i <= max_a; i++) {
        ans += mobius[i] * (quick_pow(2, cnt[i]) - 1);
        ans = (ans % MOD + MOD) % MOD;
    }
    std::cout << ans << std::endl;
    return 0;
}
