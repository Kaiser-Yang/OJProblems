// problem statement: https://www.luogu.com.cn/problem/P1171

#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> dist(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { std::cin >> dist[i][j]; }
    }
    std::vector<std::vector<int>> dp(n,
                                     std::vector<int>(1 << n, std::numeric_limits<int>::max() / 2));
    dp[0][1] = 0;
    int ans = std::numeric_limits<int>::max();
    for (int st = 1; st < (1 << n); st++) {
        for (int u = 0; u < n; u++) {
            if (!(st & (1 << u))) { continue; }
            for (int v = 0; v < n; v++) {
                if (st & (1 << v)) { continue; }
                auto &&nst = st | (1 << v);
                if (dp[v][nst] > dp[u][st] + dist[u][v]) { dp[v][nst] = dp[u][st] + dist[u][v]; }
                if (nst == (1 << n) - 1) { ans = std::min(ans, dp[v][nst] + dist[v][0]); }
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}
