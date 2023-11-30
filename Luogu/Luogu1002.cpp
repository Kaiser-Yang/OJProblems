#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 22;
constexpr int MAXM = 22;

int n, m, horseX, horseY;
int dx[] = {2, 2, 1, 1, -2, -2, -1, -1};
int dy[] = {1, -1, 2, -2, 1, -1, 2, -2};
long long dp[MAXN][MAXM];

bool bound(int x, int y)
{
    return x >= 0 && x <= n && y >= 0 && y <= m;
}

int main()
{
    cin >> n >> m >> horseX >> horseY;
    dp[horseX][horseY] = -1;
    for (int i = 0; i < sizeof(dx) / sizeof(int); i++) {
        int nx = horseX + dx[i];
        int ny = horseY + dy[i];
        if (!bound(nx, ny)) { continue; }
        dp[nx][ny] = -1;
    }
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1) {
                dp[i][j] = 0;
            } else {
                if (i - 1 >= 0) { dp[i][j] += dp[i - 1][j]; }
                if (j - 1 >= 0) { dp[i][j] += dp[i][j - 1]; }
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}