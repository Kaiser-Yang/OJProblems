// problem statement: https://www.luogu.com.cn/problem/T414961

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
static T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        i64 n, a, b;
        std::cin >> n >> a >> b;
        auto g = gcd(a, b);
        auto cnt = n / g;
        if (cnt % 2 == 1) {
            std::cout << "Yuwgna\n";
        } else {
            std::cout << "Iaka\n";
        }
    }
    return 0;
}
