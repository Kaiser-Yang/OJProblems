// problem statement:

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
static void ex_crt(const std::vector<T> &a, const std::vector<T> &m, T &x, T &l) {
    x = 0;
    l = 1;
    for (int i = 0; i < a.size(); i++) {
        T t0, _;
        T d = gcd(l, m[i]);
        if ((a[i] - x) % d != 0) {
            x = l = -1;
            return;
        }
        ex_gcd(l / d, m[i] / d, t0, _);
        t0 = (a[i] - x) / d * t0 % (m[i] / d);
        t0 = (t0 % (m[i] / d) + (m[i] / d)) % (m[i] / d);
        x = x + t0 * l;
        l = m[i] / d * l;
        x %= l;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<__int128> a(n), b(n);
    for (int i = 0; i < n; i++) {
        i64 _a, _b;
        std::cin >> _a >> _b;
        a[i] = _a;
        b[i] = _b;
    }
    __int128 x, l;
    ex_crt(b, a, x, l);
    std::cout << (i64)x << std::endl;
    return 0;
}
