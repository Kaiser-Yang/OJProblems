#include <bits/stdc++.h>

using namespace std;

void dfs(int u, int fa, vector<vector<int>> &dp, vector<vector<int>> &g) {
    dp[u][0] = 1;
    dp[u][1] = 0;
    dp[u][2] = g.size();
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) { continue; }
        dfs(v, u, dp, g);
        dp[u][0] += min(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][2];
    }
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) { continue; }
        dp[u][2] = min(dp[u][2], dp[v][0] + dp[u][1] - dp[v][2]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    int N, u, v;
    vector<vector<int>> g, dp;
    while (cin >> N) {
        g.clear();
        g.resize(N + 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dp.clear();
        dp.resize(N + 1);
        for (int i = 0; i <= N; i++) { dp[i].resize(3); }
        dfs(1, 0, dp, g);
        cout << min(dp[1][0], dp[1][2]) << endl;
        cin >> N;
        if (N == -1) { break; }
    }
    return 0;
}
