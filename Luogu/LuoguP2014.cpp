// problem statement: https://www.luogu.com.cn/problem/P2014

#include <bits/stdc++.h>

constexpr int MAXN = 3e2 + 10;
constexpr int MAXM = 3e2 + 10;

using namespace std;

int n, m, par, w[MAXN];
int dp[MAXN][MAXM];
vector<int> g[MAXN];

void dfs(int u, int m) {
    if (m == 0) { return; }
    for (auto &&v : g[u]) {
        for (int j = 0; j < m; j++) { dp[v][j] = dp[u][j]; }
        dfs(v, m - 1);
        for (int j = 1; j <= m; j++) { dp[u][j] = max(dp[u][j], dp[v][j - 1] + w[v]); }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> par >> w[i];
        g[par].push_back(i);
    }
    dfs(0, m);
    cout << dp[0][m] << endl;
    return 0;
}
