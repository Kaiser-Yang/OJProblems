// problem statement: https://www.luogu.com.cn/problem/P2054

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

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

template <typename T>
static T inverse_of(T a, T mod) {
    T x, y;
    (void)ex_gcd(a, mod, x, y);
    return (x % mod + mod) % mod;
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    __int128 n, m, l;
    i64 _n, _m, _l;
    std::cin >> _n >> _m >> _l;
    n = _n;
    m = _m;
    l = _l;
    l %= n + 1;
    __int128 inv = inverse_of<__int128>(2, n + 1);
    std::cout << (i64)(l * pow(inv, m, n + 1) % (n + 1)) << std::endl;
    return 0;
}
