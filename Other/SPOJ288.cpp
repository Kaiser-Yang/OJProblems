// problem statement: https://www.spoj.com/problems/PON/

#include <iostream>

using u64 = unsigned long long;

class miller_rabin {
public:
    template <typename T>
    static bool is_prime(T n) {
        if (n < 2) { return false; }
        if (n == 2) { return true; }
        if (n % 2 == 0) { return false; }
        short s = 0;
        T d = n - 1;
        while (d % 2 == 0) {
            d >>= 1;
            s++;
        }
        for (auto &&a : test) {
            if (a % n == 0) { continue; }
            auto x = quick_pow(a, d, n);
            if (x == 1 || x == n - 1) { continue; }
            bool ok = false;
            for (short r = 1; r < s; r++) {
                x = multiply(x, x, n);
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
    template <typename T1, typename T2, typename T3>
    static T1 quick_pow(T1 a, T2 b, T3 mod) {
        T1 res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) { res = multiply(res, a, mod); }
            a = multiply(a, a, mod);
            b >>= 1;
        }
        return res;
    }

    template <typename T1, typename T2, typename T3>
    static auto multiply(T1 a, T2 b, T3 mod) -> decltype(a * b) {
        decltype(a * b) res = 0;
        a %= mod;
        while (b) {
            if (b & 1) { res = (res + a) % mod; }
            a = (a << 1) % mod;
            b >>= 1;
        }
        return res;
    }

    static const u64 test[7];
};
constexpr u64 miller_rabin::test[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        u64 n;
        std::cin >> n;
        std::cout << (miller_rabin::is_prime(n) ? "YES\n" : "NO\n");
    }
    return 0;
}
