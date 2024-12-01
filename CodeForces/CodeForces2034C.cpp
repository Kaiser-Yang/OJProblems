// problem statement: https://codeforces.com/contest/2034/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n, m;
vector<string> a;

pair<int, int> get_next_pos(int x, int y) {
    if (a[x][y] == 'U') { return {x - 1, y}; }
    if (a[x][y] == 'D') { return {x + 1, y}; }
    if (a[x][y] == 'L') { return {x, y - 1}; }
    if (a[x][y] == 'R') { return {x, y + 1}; }
    return {x, y};
}

char get_reverse_dir(char dir) {
    if (dir == 'U') { return 'D'; }
    if (dir == 'D') { return 'U'; }
    if (dir == 'L') { return 'R'; }
    if (dir == 'R') { return 'L'; }
    return '?';
}

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

enum { UNVISITED, VISITING, TRAPPED, EXIT };
vector<vector<int>> state;

int dfs(int x, int y) {
    auto [nx, ny] = get_next_pos(x, y);
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        return state[x][y] = EXIT;
    } else if (state[nx][ny] == VISITING) {
        return state[x][y] = TRAPPED;
    } else if (state[nx][ny] == EXIT) {
        return state[x][y] = EXIT;
    } else if (state[nx][ny] == TRAPPED) {
        return state[x][y] = TRAPPED;
    } else if (state[nx][ny] == UNVISITED) {
        state[x][y] = VISITING;
        if (a[nx][ny] == '?') {
            a[nx][ny] = get_reverse_dir(a[x][y]);
            return state[x][y] = state[nx][ny] = TRAPPED;
        }
        return state[x][y] = dfs(nx, ny);
    } else {
        return -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        state.clear();
        state.resize(n, vector<int>(m, UNVISITED));
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] != '?' && state[i][j] == UNVISITED) { dfs(i, j); }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == '?') {
                    int res = EXIT;
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k], ny = j + dy[k];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) { continue; }
                        if (a[nx][ny] == '?') {
                            state[nx][ny] = TRAPPED;
                            res = TRAPPED;
                            break;
                        } else if (state[nx][ny] == TRAPPED) {
                            res = TRAPPED;
                            break;
                        }
                    }
                    state[i][j] = res;
                }
                if (state[i][j] == TRAPPED) { ans++; }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
