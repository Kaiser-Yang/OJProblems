// problem statement: https://www.luogu.com.cn/problem/P1495

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
static T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
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
static void crt(const std::vector<T> &a, const std::vector<T> &m, T &x, T &l) {
    assert(a.size() == m.size());
    x = 0;
    l = lcm(m);
    for (int i = 0; i < a.size(); i++) {
        x = (x + a[i] * (l / m[i]) % l * inverse_of(l / m[i], m[i]) % l) % l;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<__int128> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int _a, _b;
        std::cin >> _a >> _b;
        a[i] = _a;
        b[i] = _b;
    }
    __int128 x = 0, l = 0;
    crt<__int128>(b, a, x, l);
    std::cout << (i64)x << std::endl;
    return 0;
}
