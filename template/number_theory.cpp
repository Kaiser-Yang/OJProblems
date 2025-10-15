#include <cassert>
#include <cstdint>
#include <vector>

using i64 = int64_t;

class number_theory {
public:
    // return the greatest common divisor of a and b
    template <typename T>
    static T gcd(T a, T b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // return the greatest common divisor of a and b,
    // and find x and y such that ax + by = gcd(a, b)
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

    // return the inverse of a modulo mod
    template <typename T1, typename T2>
    static T2 inverse_of(T1 a, T2 mod) {
        i64 x, y;
        (void)ex_gcd(a, mod, x, y);
        return (x % mod + mod) % mod;
    }

    // return the inverse of each element in a modulo mod
    template <typename T1, typename T2>
    static std::vector<T2> inverse(const std::vector<T1> &a, T2 mod) {
        std::vector<T2> prod(a.size() + 1, 1);
        for (int i = 0; i < a.size(); i++) { prod[i + 1] = 1ull * prod[i] * (a[i] % mod) % mod; }
        std::vector<T2> inv(a.size());
        auto s = inverse_of(prod.back(), mod);
        for (int i = a.size() - 1; i >= 0; i--) {
            inv[i] = 1ull * s * prod[i] % mod;
            s = 1ull * s * a[i] % mod;
        }
        return inv;
    }

    // return the factorial of [0, n) modulo mod
    template <typename T1, typename T2>
    static std::vector<T2> factorial(T1 n, T2 mod) {
        std::vector<T2> fact(n, 1);
        for (T1 i = 2; i < n; i++) { fact[i] = 1ull * fact[i - 1] * i % mod; }
        return fact;
    }

    template <typename T1, typename T2, typename T3>
    static T3 multiply(T1 a, T2 b, T3 mod) {
        T3 res = 1;
        a %= mod;
        b %= mod;
        while (b) {
            if (b & 1) { res = (0ull + res + a) % mod; }
            a = (0ull + a + a) % mod;
            b >>= 1;
        }
        return res;
    }

    template <typename T1, typename T2, typename T3>
    static T3 pow(T1 a, T2 b, T3 mod) {
        T3 res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) { res = multiply(res, a, mod); }
            a = multiply(a, a, mod);
            b >>= 1;
        }
        return res;
    }

    template <typename T>
    static bool is_prime(T n) {
        if (n < 2) { return false; }
        if (n == 2) { return true; }
        if (n % 2 == 0) { return false; }
        int s = 0;
        T d = n - 1;
        while (d % 2 == 0) {
            d >>= 1;
            s++;
        }
        for (auto &&a : miller_rabin_test) {
            if (a % n == 0) { continue; }
            auto x = pow(a, d, n);
            if (x == 1 || x == n - 1) { continue; }
            bool ok = false;
            for (int r = 1; r < s; r++) {
                x = pow(x, 2, n);
                if (x == n - 1) {
                    ok = true;
                    break;
                }
            }
            if (!ok) { return false; }
        }
        return true;
    }

private:
    static const int miller_rabin_test[7];
};
constexpr int miller_rabin_test[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
