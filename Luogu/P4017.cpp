// problem statement: https://www.luogu.com.cn/problem/P4017

#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> in_degree(n), out_degree(n);
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        in_degree[v]++;
        out_degree[u]++;
    }
    std::vector<int> dp(n);
    constexpr int MOD = 80112002;
    auto topo_sort = [&]() {
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {
                dp[i] = 1;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &&v : g[u]) {
                dp[v] = (dp[v] + dp[u]) % MOD;
                in_degree[v]--;
                if (in_degree[v] == 0) { q.push(v); }
            }
        }
    };
    topo_sort();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (out_degree[i] == 0) { ans = (ans + dp[i]) % MOD; }
    }
    std::cout << ans << std::endl;
    return 0;
}
