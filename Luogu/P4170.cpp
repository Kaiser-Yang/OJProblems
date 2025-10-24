// problem statement: https://www.luogu.com.cn/problem/P4170

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, n));
    for (int i = 0; i < n; i++) { dp[i][i] = 1; }
    for (int len = 2; len <= n; len++) {
        for (int i = 0, j = i + len - 1; j < n; i++, j++) {
            if (s[i] == s[j]) {
                dp[i][j] = std::min(i + 1 < n ? dp[i + 1][j] : n, j - 1 >= 0 ? dp[i][j - 1] : n);
            }
            for (int k = i; k < j; k++) { dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j]); }
        }
    }
    std::cout << dp[0][n - 1] << '\n';
    return 0;
}
