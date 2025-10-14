// problem statement: https://leetcode.cn/problems/number-of-music-playlists/
#include <cstdint>
#include <vector>

using u64 = uint64_t;

class combination {
public:
    // return the factorial of [0, n) modulo mod
    template <typename T1, typename T2>
    static std::vector<T2> factorial(T1 n, T2 mod) {
        std::vector<T2> fact(n);
        fact[0] = fact[1] = 1;
        for (T1 i = 2; i < n; i++) { fact[i] = (u64)fact[i - 1] * i % mod; }
        return fact;
    }

    // return the inverse of a modulo mod
    template <typename T1, typename T2>
    static T2 inverse(T1 a, T2 mod) {
        T2 x, y;
        (void)ex_gcd(a, mod, x, y);
        return (x % mod + mod) % mod;
    }

    // return the inverse of each element in a modulo mod
    template <typename T1, typename T2>
    static std::vector<T2> inverse(const std::vector<T1> &a, T2 mod) {
        std::vector<T2> prod(a.size() + 1);
        prod[0] = 1;
        for (int i = 0; i < a.size(); i++) { prod[i + 1] = (u64)prod[i] * a[i] % mod; }
        std::vector<T2> inv(a.size());
        auto s = inverse(prod.back(), mod);
        for (int i = a.size() - 1; i >= 0; i--) {
            inv[i] = (u64)s * prod[i] % mod;
            s = (u64)s * a[i] % mod;
        }
        return inv;
    }

private:
    template <typename T1, typename T2>
    static T1 ex_gcd(T1 a, T1 b, T2 &x, T2 &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        } else {
            T1 d = ex_gcd(b, a % b, y, x);
            y -= (a / b) * x;
            return d;
        }
    }
};

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        auto fact = combination::factorial(n + 1, MOD);
        auto inv = combination::inverse(fact, MOD);
        int ans = 0;
        int sign = 1;
        for (int i = 0; i <= n - k; i++) {
            auto tmp = quick_pow(n - i - k, goal - k, MOD);
            tmp = (u64)tmp * inv[n - i - k] % MOD;
            tmp = (u64)tmp * inv[i] % MOD;
            if (sign == 1) {
                ans = (ans + tmp) % MOD;
            } else {
                ans -= tmp;
                ans = (ans % MOD + MOD) % MOD;
            }
            sign = -sign;
        }
        ans = (u64)ans * fact[n] % MOD;
        return ans;
    }

    template <typename T1, typename T2, typename T3>
    static T1 quick_pow(T1 a, T2 b, T3 mod) {
        T1 res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) { res = (u64)res * a % mod; }
            a = (u64)a * a % mod;
            b >>= 1;
        }
        return res;
    }
    static constexpr int MOD = 1e9 + 7;
};
