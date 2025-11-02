// problem statement: https://www.luogu.com.cn/problem/P2252

#include <cmath>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const long double phi = (std::sqrt(5.L) + 1.) / 2.;
    i64 a, b;
    std::cin >> a >> b;
    if (a > b) { std::swap(a, b); }
    if (a == i64((b - a) * phi)) {
        std::cout << "0\n";
    } else {
        std::cout << "1\n";
    }
    return 0;
}
