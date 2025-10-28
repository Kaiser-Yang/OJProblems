// problem statement: https://www.luogu.com.cn/problem/P1759

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m, v, n;
    std::cin >> m >> v >> n;
    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) { std ::cin >> a[i] >> b[i] >> c[i]; }
    std::vector<std::vector<std::vector<int>>> dp(
        n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(v + 1, 0)));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= v; k++) {
                dp[i][j][k] = dp[i + 1][j][k];
                if (j >= a[i] && k >= b[i]) {
                    dp[i][j][k] = std::max(dp[i][j][k], dp[i + 1][j - a[i]][k - b[i]] + c[i]);
                }
            }
        }
    }
    std::cout << dp[0][m][v] << "\n";
    for (int i = 0, j = m, k = v; i < n; i++) {
        if (j >= a[i] && k >= b[i] && dp[i][j][k] == dp[i + 1][j - a[i]][k - b[i]] + c[i]) {
            std::cout << i + 1 << " ";
            j -= a[i];
            k -= b[i];
        }
    }
    std::cout << std::endl;
    return 0;
}
