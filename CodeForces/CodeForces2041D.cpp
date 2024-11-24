// problem statement: https://codeforces.com/contest/2041/problem/D

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<string> mp;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs() {
    int sx = -1, sy = -1, ex = -1, ey = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == 'S') {
                sx = i, sy = j;
            } else if (mp[i][j] == 'T') {
                ex = i, ey = j;
            }
        }
    }
    struct State {
        int x, y, direction, cnt;
        State(int x, int y, int direction, int cnt) : x(x), y(y), direction(direction), cnt(cnt) {}
    };
    queue<State> q;
    vector<vector<vector<vector<int>>>> dis(
        n,
        vector<vector<vector<int>>>(
            m, vector<vector<int>>(4, vector<int>(4, numeric_limits<int>::max() / 2))));
    q.push(State(sx, sy, 0, 0));
    q.push(State(sx, sy, 1, 0));
    q.push(State(sx, sy, 2, 0));
    q.push(State(sx, sy, 3, 0));
    dis[sx][sy][0][0] = 0;
    dis[sx][sy][1][0] = 0;
    dis[sx][sy][2][0] = 0;
    dis[sx][sy][3][0] = 0;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = u.x + dx[i], y = u.y + dy[i];
            if (x >= 0 && x < n && y >= 0 && y < m && mp[x][y] != '#') {
                int cnt = (i == u.direction ? u.cnt + 1 : 1);
                if (cnt <= 3 && dis[x][y][i][cnt] > dis[u.x][u.y][u.direction][u.cnt] + 1) {
                    dis[x][y][i][cnt] = dis[u.x][u.y][u.direction][u.cnt] + 1;
                    q.push(State(x, y, i, cnt));
                }
            }
        }
    }
    int ans = numeric_limits<int>::max() / 2;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans = min(ans, dis[ex][ey][i][j]);
        }
    }
    cout << (ans == numeric_limits<int>::max() / 2 ? -1 : ans) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    mp.resize(n);
    for (int i = 0; i < n; i++) { cin >> mp[i]; }
    bfs();
    return 0;
}
