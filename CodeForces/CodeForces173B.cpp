#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e3 + 10;
constexpr int MAXM = 1e3 + 10;
constexpr int INF = 0X3f3f3f3f;

int n, m;
string grid[MAXN];
int dis[MAXN][MAXM][4];

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    MAX_DIRECTION,
};
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool bound(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }

void bfs() {
    struct Node {
        int x, y, direction;
    };
    deque<Node> q;
    memset(dis, 0x3f, sizeof(dis));
    q.push_front({0, 0, RIGHT});
    dis[0][0][RIGHT] = 0;
    while (!q.empty()) {
        auto front = q.front();
        q.pop_front();
        int x = front.x, y = front.y, direction = front.direction;
        int nx = x + dx[direction], ny = y + dy[direction];
        if (bound(nx, ny) && dis[nx][ny][direction] > dis[x][y][direction]) {
            dis[nx][ny][direction] = dis[x][y][direction];
            q.push_front({nx, ny, direction});
        }
        if (grid[x][y] == '#') {
            for (int nDirection = 0; nDirection < MAX_DIRECTION; nDirection++) {
                if (nDirection == direction) { continue; }
                if (dis[x][y][nDirection] > dis[x][y][direction] + 1) {
                    dis[x][y][nDirection] = dis[x][y][direction] + 1;
                    q.push_back({x, y, nDirection});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) { cin >> grid[i]; }
    bfs();
    if (dis[n - 1][m - 1][3] == INF) {
        cout << "-1\n";
    } else {
        cout << dis[n - 1][m - 1][3] << endl;
    }
    return 0;
}
