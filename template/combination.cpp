#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

class combination {
public:
    // return the factorial of [0, n) modulo mod
    template <typename T1, typename T2>
    static std::vector<T2> factorial(T1 n, T2 mod) {
        std::vector<T2> fact(n, 1);
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
        std::vector<T2> prod(a.size() + 1, 1);
        for (int i = 0; i < a.size(); i++) { prod[i + 1] = (u64)prod[i] * a[i] % mod; }
        std::vector<T2> inv(a.size());
        auto s = inverse(prod.back(), mod);
        for (int i = a.size() - 1; i >= 0; i--) {
            inv[i] = (u64)s * prod[i] % mod;
            s = (u64)s * a[i] % mod;
        }
        return inv;
    }

    // initialize the factorial and inverse factorial arrays
    // required before calling 'c' and 'p'
    template <typename T1>
    void init(T1 n, u64 mod) {
        fact = factorial(n + 1, mod);
        fact_inv = inverse(fact, mod);
        combination::mod = mod;
        initialized = true;
    }

    // return the combination of n choose m modulo mod
    template <typename T, typename R = i64>
    static R c(T n, T m) {
        // We use i64 as the default return type to avoid underflow of unsigned types.
        return R(p(n, m) * fact_inv[m] % mod);
    }

    // return the permutation of n P m modulo mod
    template <typename T, typename R = i64>
    static R p(T n, T m) {
        assert(initialized);
        assert(n >= m);
        // We use i64 as the default return type to avoid underflow of unsigned types.
        return R(fact[n] * fact_inv[n - m] % mod);
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
    static bool initialized;
    static std::vector<u64> fact;
    static std::vector<u64> fact_inv;
    static u64 mod;
};
bool combination::initialized = false;
std::vector<u64> combination::fact;
std::vector<u64> combination::fact_inv;
u64 combination::mod = std::numeric_limits<u64>::max();
