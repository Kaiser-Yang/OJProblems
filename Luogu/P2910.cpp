// problem statement: https://www.luogu.com.cn/problem/P2910

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(m);
    for (int i = 0; i < m; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    std::vector<std::vector<u64>> dp(n, std::vector<u64>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { std::cin >> dp[i][j]; }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] + dp[k][j] < dp[i][j]) { dp[i][j] = dp[i][k] + dp[k][j]; }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < m; i++) { ans += dp[a[i - 1]][a[i]]; }
    std::cout << ans << std::endl;
    return 0;
}
