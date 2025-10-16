// problem statement: https://www.luogu.com.cn/problem/P1516

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    i64 x, y, m, n, L;
    std::cin >> x >> y >> m >> n >> L;
    if (m < n) {
        std::swap(m, n);
        std::swap(x, y);
    }
    i64 X, _;
    auto g = ex_gcd<i64>(m - n, L, X, _);
    if ((y - x) % g) {
        std::cout << "Impossible\n";
        return 0;
    }
    i64 dx = L / g;
    X *= (y - x) / g;
    X = (X % dx + dx) % dx;
    if (X == 0) { X += dx; }
    std::cout << X << std::endl;
    return 0;
}
