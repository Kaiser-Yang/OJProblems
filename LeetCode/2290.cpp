// problem statement:
// https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/description/

#include <deque>
#include <limits>
#include <vector>

class Solution {
public:
    int minimumObstacles(std::vector<std::vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        std::vector<std::vector<int>> dist(n, std::vector<int>(m, std::numeric_limits<int>::max()));
        std::deque<std::pair<int, int>> q;
        static constexpr int dx[] = {0, 0, 1, -1};
        static constexpr int dy[] = {1, -1, 0, 0};
        dist[0][0] = (grid[0][0] == 1);
        q.push_front({0, 0});
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m ||
                    dist[nx][ny] <= dist[x][y] + (grid[nx][ny] == 1)) {
                    continue;
                }
                dist[nx][ny] = dist[x][y] + (grid[nx][ny] == 1);
                if (grid[nx][ny] == 1) {
                    q.push_back({nx, ny});
                } else {
                    q.push_front({nx, ny});
                }
            }
        }
        return dist[n - 1][m - 1];
    }
};
