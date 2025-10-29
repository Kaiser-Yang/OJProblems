// problem statement: https://www.luogu.com.cn/problem/P4018

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        std::cout << (n % 6 == 0 ? "Roy wins!\n" : "October wins!\n");
    }
    return 0;
}
