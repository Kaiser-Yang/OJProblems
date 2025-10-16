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

    template <typename T>
    static T gcd(const std::vector<T> &a) {
        T res = 0;
        for (auto &&x : a) { res = gcd(res, x); }
        return res;
    }

    template <typename T>
    static T lcm(T a, T b) {
        return a / gcd(a, b) * b;
    }

    template <typename T>
    static T lcm(const std::vector<T> &a) {
        T res = 1;
        for (auto &&x : a) { res = lcm(res, x); }
        return res;
    }

    // return the greatest common divisor of a and b,
    // and find x and y such that ax + by = gcd(a, b)
    template <typename T>
    static T ex_gcd(T a, T b, T &x, T &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        } else {
            T d = ex_gcd(b, a % b, y, x);
            y -= (a / b) * x;
            return d;
        }
    }

    // return the inverse of a modulo mod
    template <typename T>
    static T inverse_of(T a, T mod) {
        T x, y;
        (void)ex_gcd(a, mod, x, y);
        return (x % mod + mod) % mod;
    }

    // return the inverse of each element in a modulo mod
    template <typename T>
    static std::vector<T> inverse(const std::vector<T> &a, T mod) {
        std::vector<T> prod(a.size() + 1, 1);
        for (int i = 0; i < a.size(); i++) { prod[i + 1] = prod[i] * (a[i] % mod) % mod; }
        std::vector<T> inv(a.size());
        auto s = inverse_of(prod.back(), mod);
        for (int i = a.size() - 1; i >= 0; i--) {
            inv[i] = s * prod[i] % mod;
            s = s * a[i] % mod;
        }
        return inv;
    }

    // return the factorial of [0, n) modulo mod
    template <typename T>
    static std::vector<T> factorial(T n, T mod) {
        std::vector<T> fact(n, 1);
        for (T i = 2; i < n; i++) { fact[i] = fact[i - 1] * i % mod; }
        return fact;
    }

    template <typename T>
    static T pow(T a, T b, T mod) {
        T res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) { res = 1ull * res * a % mod; }
            a = 1ull * a * a % mod;
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

    // solve the system of linear congruences:
    // x ≡ a1 (mod m1)
    // x ≡ a2 (mod m2)
    // ...
    // x ≡ an (mod mn)
    // return the solution x (minimal and positive) and the lcm of m1, m2, ..., mn
    template <typename T>
    static void crt(const std::vector<T> &a, const std::vector<T> &m, T &x, T &l) {
        assert(a.size() == m.size());
        x = 0;
        l = lcm(m);
        for (int i = 0; i < a.size(); i++) {
            x = (x + a[i] * (l / m[i]) % l * inverse_of(l / m[i], m[i]) % l) % l;
        }
    }

private:
    static const int miller_rabin_test[7];
};
constexpr int miller_rabin_test[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
