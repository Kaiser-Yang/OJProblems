// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXR              = 110;
constexpr int MAXC              = 110;
constexpr int MAX_DIRECTION_NUM = 4;

int r, c, ans;
int grid[MAXR][MAXC], dp[MAXR][MAXC];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool bound(int x, int y) { return x >= 0 && x < r && y >= 0 && y < c; }

int dfs(int x, int y) {
    if (dp[x][y] != 0) { return dp[x][y]; }
    int temp = 0;
    for (int i = 0; i < MAX_DIRECTION_NUM; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!bound(nx, ny) || grid[nx][ny] >= grid[x][y]) { continue; }
        temp = max(temp, dfs(nx, ny));
    }
    return dp[x][y] = temp + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) { cin >> grid[i][j]; }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (dp[i][j] == 0) { dfs(i, j); }
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}