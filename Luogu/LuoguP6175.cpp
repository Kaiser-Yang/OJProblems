// problem statement: https://www.luogu.com.cn/problem/P6175
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;
constexpr int INF  = 0x3f3f3f3f;

int n, m, u, v, w, ans = INF;
int dp[MAXN][MAXN], g[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    memset(dp, 0x3f, sizeof(dp));
    memset(g, 0x3f, sizeof(g));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { dp[i][i] = g[i][i] = 0; }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = dp[u][v] = dp[v][u] = min(dp[u][v], w);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || i == k || j == k || dp[i][j] == INF || g[i][k] == INF ||
                    g[k][j] == INF) {
                    continue;
                }
                ans = min(ans, dp[i][j] + g[i][k] + g[k][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) { dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]); }
        }
    }
    cout << (ans == INF ? "No solution." : to_string(ans)) << endl;
    return 0;
}
