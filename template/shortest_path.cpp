#include <limits>
#include <tuple>
#include <utility>
#include <vector>

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
