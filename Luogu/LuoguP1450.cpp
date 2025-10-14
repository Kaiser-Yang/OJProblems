// problem statement: https://www.luogu.com.cn/problem/P1450

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;

int main() {
    constexpr int n = 4;
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) { std::cin >> c[i]; }
    constexpr int W = 1e5;
    std::array<i64, W + 1> f;
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = c[i]; j <= W; j++) { f[j] += f[j - c[i]]; }
    }
    int T;
    std::cin >> T;
    while (T--) {
        std::vector<int> cnt(n);
        for (int i = 0; i < n; i++) { std::cin >> cnt[i]; }
        int S;
        std::cin >> S;
        i64 res = 0;
        for (int s = 0; s < (1 << n); s++) {
            int sign = 1;
            i64 tmp = 0;
            for (int i = 0; i < n; i++) {
                if (s & (1 << i)) {
                    tmp += c[i] * (cnt[i] + 1);
                    sign = -sign;
                }
            }
            if (tmp > S) { continue; }
            res += sign * f[S - tmp];
        }
        std::cout << res << '\n';
    }
    return 0;
}
