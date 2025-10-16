// problem statement: https://www.luogu.com.cn/problem/P4774

#include <cassert>
#include <cstdint>
#include <iostream>
#include <set>
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<__int128> a(n), p(n), bonus(n);
        std::multiset<__int128> sword;
        for (int i = 0; i < n; i++) {
            i64 _a;
            std::cin >> _a;
            a[i] = _a;
        }
        for (int i = 0; i < n; i++) {
            i64 _p;
            std::cin >> _p;
            p[i] = _p;
        }
        for (int i = 0; i < n; i++) {
            i64 _b;
            std::cin >> _b;
            bonus[i] = _b;
        }
        for (int i = 0; i < m; i++) {
            i64 s;
            std::cin >> s;
            sword.insert(s);
        }
        std::vector<__int128> b(n);
        __int128 min_ans = 0;
        for (int i = 0; i < n; i++) {
            auto it = sword.upper_bound(a[i]);
            if (it != sword.begin()) { it--; }
            assert(it != sword.end());
            b[i] = *it;
            min_ans = std::max(min_ans, (a[i] - 1) / b[i] + 1);
            sword.erase(it);
            sword.insert(bonus[i]);
        }
        __int128 x = 0, l = 1;
        for (int i = 0; i < n; i++) {
            __int128 t0, _;
            __int128 d = gcd(b[i] * l, p[i]);
            if ((a[i] - b[i] * x) % d) {
                x = l = -1;
                break;
            }
            ex_gcd(b[i] * l / d, p[i] / d, t0, _);
            t0 = (a[i] - b[i] * x) / d * t0 % (p[i] / d);
            t0 = (t0 % (p[i] / d) + (p[i] / d)) % (p[i] / d);
            x = x + t0 * l;
            l = p[i] / d * l;
            x %= l;
        }
        if (x != -1 && x < min_ans) { x += ((min_ans - x - 1) / l + 1) * l; }
        std::cout << (i64)x << '\n';
    }
    return 0;
}
