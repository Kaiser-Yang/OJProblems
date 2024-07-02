// problem statement: https://www.luogu.com.cn/problem/P4011

#include <bits/stdc++.h>

constexpr int MAXN = 10 + 2;
constexpr int MAXM = 10 + 2;
constexpr int MAXP = 10 + 2;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, p, k, a1, b1, a2, b2, g, s, q;
int barrier[MAXN][MAXM][MAXN][MAXM];
vector<int> key[MAXN][MAXM];
int dis[MAXN][MAXM][1 << 10];
bool vis[MAXN][MAXM][1 << 10];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool hasKey(int s, int i) { return (s & (1 << (i - 1))) != 0; }

int getKeySet(int x, int y) {
    int res = 0;
    for (const auto &key : ::key[x][y]) { res |= 1 << (key - 1); }
    return res;
}

int bfs() {
    struct State {
        int x, y, keySet;
    };
    queue<State> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    int startKeySet = getKeySet(1, 1);
    q.push({1, 1, startKeySet});
    dis[1][1][startKeySet] = 0;
    vis[1][1][startKeySet] = true;
    while (!q.empty()) {
        auto now = q.front();
        if (now.x == n && now.y == m) { return dis[n][m][now.keySet]; }
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m || barrier[now.x][now.y][nx][ny] == 0 ||
                (barrier[now.x][now.y][nx][ny] != -1 &&
                 !hasKey(now.keySet, barrier[now.x][now.y][nx][ny]))) {
                continue;
            }
            int newKeySet = (now.keySet | getKeySet(nx, ny));
            if (vis[nx][ny][newKeySet]) { continue; }
            vis[nx][ny][newKeySet] = true;
            dis[nx][ny][newKeySet] = dis[now.x][now.y][now.keySet] + 1;
            q.push({nx, ny, newKeySet});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    memset(barrier, 0xff, sizeof(barrier));
    cin >> n >> m >> p;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> a1 >> b1 >> a2 >> b2 >> g;
        barrier[a1][b1][a2][b2] = barrier[a2][b2][a1][b1] = g;
    }
    cin >> s;
    for (int i = 0; i < s; i++) {
        cin >> a1 >> b1 >> q;
        key[a1][b1].push_back(q);
    }
    cout << bfs() << "\n";
    return 0;
}
