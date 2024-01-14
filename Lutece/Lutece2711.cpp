#include <bits/stdc++.h>

using namespace std;

int n, m;
int dis[505][505];
vector<string> grid;
queue<pair<int, int>> q;

int dx[] = {-1, -1, +1, +1};
int dy[] = {-1, +1, +1, -1};

bool bound(int x, int y)
{
    return x >= 0 && x <= n && y >= 0 && y <= m;
}

bool connected(int i, int x, int y)
{
    if (i == 0) {
        return grid[x][y] == '\\';
    }
    if (i == 1) {
        return grid[x][y + 1] == '/';
    }
    if (i == 2) {
        return grid[x + 1][y + 1] == '\\';
    }
    return grid[x + 1][y] == '/';
}

void dfs(int x, int y)
{
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!bound(nx, ny) || dis[nx][ny] != -1 || !connected(i, x, y)) { continue; }
        dis[nx][ny] = dis[x][y];
        q.push({nx, ny});
        dfs(nx, ny);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(dis, -1, sizeof(dis));
    cin >> n >> m;
    grid.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> grid[i];
        grid[i] = " " + grid[i];
    }
    q.push({0, 0});
    dis[0][0] = 0;
    dfs(0, 0);
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        int x = front.first;
        int y = front.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!bound(nx, ny) || dis[nx][ny] != -1 || connected(i, x, y)) { continue; }
            q.push({nx, ny});
            dis[nx][ny] = dis[x][y] + 1;
            dfs(nx, ny);
        }
    }
    if (dis[n][m] == -1) {
        cout << "NO SOLUTION" << endl;
    } else {
        cout << dis[n][m] << endl;
    }
    return 0;
}