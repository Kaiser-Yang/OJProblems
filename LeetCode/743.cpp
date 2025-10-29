// problems statement: https://leetcode.cn/problems/network-delay-time/

#include <limits>
#include <tuple>
#include <vector>

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
        std::vector<std::tuple<int, int, int>> edges;
        for (auto &&time : times) { edges.push_back({time[0] - 1, time[1] - 1, time[2]}); }
        auto dist = bellman_ford(edges, n, k - 1).first;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] == std::numeric_limits<int>::max()) { return -1; }
            ans = std::max(ans, dist[i]);
        }
        return ans;
    }
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
