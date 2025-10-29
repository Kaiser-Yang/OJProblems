// problem statement: https://leetcode.cn/problems/cheapest-flights-within-k-stops/

#include <limits>
#include <queue>
#include <vector>

class Solution {
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src, int dst, int k) {
        k += 2;
        std::vector<std::vector<std::pair<int, int>>> g(n);
        for (auto &&flight : flights) {
            int u = flight[0], v = flight[1], w = flight[2];
            g[u].push_back({v, w});
        }
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<int>> dist(
            n, std::vector<int>(k + 1, std::numeric_limits<int>::max()));
        q.push({src, 1});
        dist[src][1] = 0;
        while (!q.empty()) {
            auto [u, stops] = q.front();
            q.pop();
            if (stops >= k) { continue; }
            for (auto &&[v, w] : g[u]) {
                if (dist[u][stops] + w < dist[v][stops + 1]) {
                    dist[v][stops + 1] = dist[u][stops] + w;
                    q.push({v, stops + 1});
                }
            }
        }
        int ans = std::numeric_limits<int>::max();
        for (int kk = 2; kk <= k; kk++) { ans = std::min(ans, dist[dst][kk]); }
        return ans == std::numeric_limits<int>::max() ? -1 : ans;
    }
};
