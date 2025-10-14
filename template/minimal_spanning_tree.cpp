#include <array>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

class minimal_spanning_tree {
public:
    template <typename T, typename R = T>
    static std::pair<std::vector<std::array<int, 2>>, R> prim(
        const std::vector<std::vector<T>> &cost) {
        int n = cost.size();
        std::vector<bool> vis(n);
        std::vector<R> dist(n, std::numeric_limits<R>::max());
        std::vector<int> parent(n, -1);
        std::vector<std::array<int, 2>> edges;
        dist[0] = 0;
        R res = 0;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!vis[j] && (u == -1 || dist[j] < dist[u])) { u = j; }
            }
            assert(u != -1);
            vis[u] = true;
            res += dist[u];
            if (parent[u] != -1) { edges.push_back({u, parent[u]}); }
            for (int v = 0; v < n; v++) {
                if (!vis[v] && cost[u][v] < dist[v]) {
                    dist[v] = cost[u][v];
                    parent[v] = u;
                }
            }
        }
        return {edges, res};
    }
};
