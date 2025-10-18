// problem statement: https://www.luogu.com.cn/problem/P5656

#include <cstdint>
#include <iostream>

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
        i64 a, b, c;
        std::cin >> a >> b >> c;
        auto g = gcd(a, b);
        if (c % g) {
            std::cout << "-1\n";
            continue;
        }
        i64 x, y;
        (void)ex_gcd(a, b, x, y);
        x *= c / g;
        y *= c / g;
        i64 dx = b / g, dy = a / g;
        i64 minimal_x = (x % dx + dx) % dx, minimal_y = (y % dy + dy) % dy;
        if (minimal_x == 0) { minimal_x += dx; }
        if (minimal_y == 0) { minimal_y += dy; }
        if ((c - a * minimal_x) / b <= 0) {
            std::cout << minimal_x << ' ' << minimal_y << '\n';
            continue;
        }
        i64 cnt = (c - a * minimal_x) / b / dy;
        if ((c - a * minimal_x) / b % dy) { cnt++; }
        std::cout << cnt << ' ' << minimal_x << ' ' << minimal_y << ' ' << (c - b * minimal_y) / a
                  << ' ' << (c - a * minimal_x) / b << '\n';
    }
    return 0;
}
