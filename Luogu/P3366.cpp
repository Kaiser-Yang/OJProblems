// problem statement: https://www.luogu.com.cn/problem/P3366
// Tag: having been in my blog

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

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
    // assert(edges.size() == n - 1);
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

template <typename T, typename R>
static std::pair<std::vector<std::tuple<int, int, T>>, R> kruskal(
    std::vector<std::tuple<int, int, T>> &edges,
    R _ = int()) {
    int n = 0;
    for (int i = 0; i < edges.size(); i++) {
        n = std::max(n, std::get<0>(edges[i]) + 1);
        n = std::max(n, std::get<1>(edges[i]) + 1);
    }
    std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
        return std::get<2>(a) < std::get<2>(b);
    });
    std::vector<std::tuple<int, int, T>> mst_edges;
    R res = 0;
    int cnt = 0;
    struct ufs {
        std::vector<int> h;

        ufs(int n) : h(n) { std::iota(h.begin(), h.end(), 0); }

        int find(int u) { return h[u] == u ? u : h[u] = find(h[u]); }

        bool same(int u, int v) { return find(u) == find(v); }

        void unite(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) { return; }
            h[v] = u;
        }
    } uf(n);
    for (auto &&[u, v, w] : edges) {
        if (uf.same(u, v)) { continue; }
        uf.unite(u, v);
        mst_edges.emplace_back(u, v, w);
        res += w;
        cnt++;
        if (cnt == n - 1) { break; }
    }
    if (cnt < n - 1) { return {{}, 0}; }
    return {mst_edges, res};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    std::vector<std::vector<int>> cost(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        cost[u][v] = cost[v][u] = std::min(cost[u][v], w);
        edges.push_back({u, v, w});
    }
    auto &&[edges1, res1] = prim(cost, 0ll);
    auto &&[edges2, res2] = prim(g, 0ll);
    auto &&[edges3, res3] = kruskal(edges, 0ll);
    assert(edges1.size() == edges2.size() && edges2.size() == edges3.size());
    assert(res1 == res2 && res2 == res3);
    if (edges1.size() != n - 1) {
        std::cout << "orz\n";
    } else {
        std::cout << res1 << '\n';
    }
    return 0;
}
