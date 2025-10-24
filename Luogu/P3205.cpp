// problem statement: https://www.luogu.com.cn/problem/P3205

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr int MOD = 19650827;
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    std::vector<std::vector<std::array<int, 2>>> dp(n, std::vector<std::array<int, 2>>(n, {0, 0}));
    for (int i = 0; i < n; i++) { dp[i][i][0] = 1; }
    for (int len = 2; len <= n; len++) {
        for (int i = 0, j = i + len - 1; j < n; i++, j++) {
            if (i + 1 < n && a[i] < a[i + 1]) { dp[i][j][0] = dp[i + 1][j][0]; }
            if (i + 1 < n && a[i] < a[j]) { dp[i][j][0] = (dp[i][j][0] + dp[i + 1][j][1]) % MOD; }
            if (j - 1 >= 0 && a[j] > a[j - 1]) { dp[i][j][1] = dp[i][j - 1][1]; }
            if (j - 1 >= 0 && a[j] > a[i]) { dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0]) % MOD; }
        }
    }
    std::cout << (dp[0][n - 1][0] + dp[0][n - 1][1]) % MOD << '\n';
    return 0;
}
