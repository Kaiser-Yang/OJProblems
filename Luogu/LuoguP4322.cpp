// problem statement: https://www.luogu.com.cn/problem/P4322

#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int k, n;
    std::cin >> k >> n;
    std::vector<int> cost(n + 1), value(n + 1);
    std::vector<double> w(n + 1);
    std::vector<std::vector<int>> g(n + 1);
    double left = 0, right = 0, ans = 0.;
    for (int i = 1; i <= n; i++) {
        int r;
        std::cin >> cost[i] >> value[i] >> r;
        right += value[i];
        g[r].push_back(i);
    }
    std::vector<std::vector<double>> dp(
        n + 1, std::vector<double>(k + 2, std::numeric_limits<double>::lowest()));
    std::function<int(int)> dfs = [&](int u) -> int {
        int p = 1;
        dp[u][1] = w[u];
        for (int v : g[u]) {
            auto size_v = dfs(v);
            for (int i = std::min(p, k + 1); i > 0; i--) {
                for (int j = 1; j <= size_v && i + j <= k + 1; j++) {
                    if (dp[u][i] == std::numeric_limits<double>::lowest() ||
                        dp[v][j] == std::numeric_limits<double>::lowest()) {
                        continue;
                    }
                    dp[u][i + j] = std::max(dp[u][i + j], dp[u][i] + dp[v][j]);
                }
            }
            p += size_v;
        }
        return p;
    };
    auto check = [&](double x) -> bool {
        for (int i = 1; i <= n; i++) { w[i] = value[i] - x * cost[i]; }
        for (int i = 0; i <= n; i++) {
            std::fill(dp[i].begin(), dp[i].end(), std::numeric_limits<double>::lowest());
        }
        dfs(0);
        return dp[0][k + 1] >= 0;
    };
    while (right - left >= 1e-5) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(3) << ans << std::endl;
    return 0;
}
