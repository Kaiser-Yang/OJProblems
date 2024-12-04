// problem satement: https://codeforces.com/problemset/problem/1236/D

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<vector<int>> r, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    r.resize(n + 1);
    c.resize(m + 1);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        r[x].push_back(y);
        c[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) { sort(r[i].begin(), r[i].end()); }
    for (int i = 1; i <= m; i++) { sort(c[i].begin(), c[i].end()); }
    bool flag = false;
    long long sum = 1;
    int x = 1, y = 1, turn = 1;
    int rx = n + 1, ry = m + 1, lx = 0, ly = 0;
    while (true) {
        int nx = 0, ny = 0;
        if (turn == 1) {
            nx = x, ny = lower_bound(r[x].begin(), r[x].end(), y) - r[x].begin();
            if (ny == r[x].size()) {
                ny = ry - 1;
            } else {
                ny = min(ry - 1, r[x][ny] - 1);
            }
            lx = x;
            turn++;
        } else if (turn == 2) {
            ny = y, nx = lower_bound(c[y].begin(), c[y].end(), x) - c[y].begin();
            if (nx == c[y].size()) {
                nx = rx - 1;
            } else {
                nx = min(rx - 1, c[y][nx] - 1);
            }
            ry = y;
            turn++;
        } else if (turn == 3) {
            nx = x, ny = lower_bound(r[x].begin(), r[x].end(), y) - r[x].begin() - 1;
            if (ny < 0) {
                ny = ly + 1;
            } else {
                ny = max(ly + 1, r[x][ny] + 1);
            }
            rx = x;
            turn++;
        } else {
            ny = y, nx = lower_bound(c[y].begin(), c[y].end(), x) - c[y].begin() - 1;
            if (nx < 0) {
                nx = lx + 1;
            } else {
                nx = max(lx + 1, c[y][nx] + 1);
            }
            ly = y;
            turn = 1;
        }
        if (x == nx && y == ny && flag) break;
        sum += abs(nx - x) + abs(ny - y);
        x = nx, y = ny;
        flag = true;
    }
    if (sum == 1LL * n * m - k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
