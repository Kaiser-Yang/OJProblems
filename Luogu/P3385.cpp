// problem statement: https://www.luogu.com.cn/problem/P3385

#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

class shortest_path {
public:
    // return dist, has_negative_cycle
    template <typename T, typename R = int>
    static std::pair<std::vector<R>, bool> bellman_ford(
        const std::vector<std::tuple<int, int, T>> &edges,
        int n,
        int s,
        R inf = std::numeric_limits<R>::max()) {
        std::vector<R> dist(n, inf);
        dist[s] = 0;
        for (int i = 0; i < n - 1; i++) {
            for (auto &&[u, v, w] : edges) {
                if (dist[u] != inf && dist[u] + w < dist[v]) { dist[v] = dist[u] + w; }
            }
        }
        // check for negative weight cycle
        for (auto &&[u, v, w] : edges) {
            if (dist[u] != inf && dist[u] + w < dist[v]) {
                return {dist, true};  // negative weight cycle detected
            }
        }
        return {dist, false};
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            u--;
            v--;
            edges.push_back({u, v, w});
            if (w >= 0) { edges.push_back({v, u, w}); }
        }
        std::cout
            << (shortest_path::bellman_ford(edges, n, 0, std::numeric_limits<i64>::max()).second ?
                    "YES\n" :
                    "NO\n");
    }
    return 0;
}
