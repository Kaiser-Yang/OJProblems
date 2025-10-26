// problem statement: https://www.luogu.com.cn/problem/P1616

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t, m;
    std::cin >> t >>m;
    std::vector<int> a(m), b(m);
    for (int i= 0; i < m; i++) { std::cin >> a[i] >> b[i]; }
    std::vector<i64> dp(t + 1, 0);
    for (int i = 0; i < m; i++) {
        for (int j = a[i]; j <= t; j++) {
            dp[j] = std::max(dp[j], dp[j - a[i]] + b[i]);
        }
    }
    std::cout << dp[t] << "\n";
    return 0;
}
