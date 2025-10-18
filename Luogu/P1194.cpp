// problem statement: https://www.luogu.com.cn/problem/P1194

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T, typename R = int>
static std::pair<std::vector<std::tuple<int, int, T>>, R> prim(
    const std::vector<std::vector<T>> &cost,
    R _ = int()) {
    int n = cost.size();
    assert(n > 0);
    std::vector<bool> vis(n);
    std::vector<T> dist(n, std::numeric_limits<T>::max());
    std::vector<int> parent(n, -1);
    std::vector<std::tuple<int, int, T>> edges;
    dist[0] = 0;
    R res = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] &&
                (u == -1 && dist[j] != std::numeric_limits<T>::max() || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1) {
            return {{}, 0};  // graph is not connected
        }
        assert(u != -1);
        vis[u] = true;
        res += dist[u];
        if (parent[u] != -1) { edges.emplace_back(u, parent[u], cost[u][parent[u]]); }
        for (int v = 0; v < n; v++) {
            if (!vis[v] && cost[u][v] < dist[v]) {
                dist[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }
    assert(edges.size() == n - 1);
    return {edges, res};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int A, B;
    std::cin >> A >> B;
    std::vector<std::vector<int>> cost(B + 1,
                                       std::vector<int>(B + 1, std::numeric_limits<int>::max()));
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            std::cin >> cost[i][j];
            if (cost[i][j] == 0) { cost[i][j] = std::numeric_limits<int>::max(); }
        }
    }
    for (int i = 0; i < B; i++) { cost[B][i] = cost[i][B] = A; }
    auto &&[_, ans] = prim(cost);
    std::cout << ans << '\n';
    return 0;
}
