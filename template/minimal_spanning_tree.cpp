#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

class minimal_spanning_tree {
public:
    template <typename T, typename R>
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
            if (parent[u] != -1) { edges.push_back({u, parent[u], cost[u][parent[u]]}); }
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

    template <typename T, typename R>
    static std::pair<std::vector<std::tuple<int, int, T>>, R> prim(
        const std::vector<std::vector<std::pair<int, T>>> &g,
        R _ = int()) {
        int n = g.size();
        assert(n > 0);
        std::priority_queue<std::tuple<T, int, int>,
                            std::vector<std::tuple<T, int, int>>,
                            std::greater<>>
            q;
        std::vector<T> dist(n, std::numeric_limits<T>::max());
        std::vector<bool> vis(n);
        std::vector<std::tuple<int, int, T>> edges;
        dist[0] = 0;
        q.push({0, 0, -1});
        R res = 0;
        while (!q.empty()) {
            auto [d, u, par] = q.top();
            assert(u < n && par < n);
            q.pop();
            if (vis[u]) { continue; }
            if (par != -1) { edges.push_back({u, par, d}); }
            vis[u] = true;
            res += d;
            for (auto &&[v, w] : g[u]) {
                if (w < dist[v]) {
                    dist[v] = w;
                    q.push({w, v, u});
                }
            }
        }
        if (edges.size() != n - 1) {
            return {{}, 0};  // graph is not connected
        }
        return {edges, res};
    }
};
