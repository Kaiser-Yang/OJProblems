#include <bits/stdc++.h>

using namespace std;

pair<int, bool> dfs(int u,
                    vector<vector<int>> &dp,
                    vector<vector<bool>> &isUnique,
                    vector<vector<int>> &g) {
    if (g[u].size() == 0) {
        dp[u][0] = 0;
        dp[u][1] = 1;
        isUnique[u][0] = isUnique[u][1] = true;
        return {1, true};
    }
    dp[u][1] = 1;
    dp[u][0] = 0;
    isUnique[u][1] = true;
    isUnique[u][0] = true;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        dfs(v, dp, isUnique, g);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
        isUnique[u][1] = isUnique[u][1] && isUnique[v][0];
        if (dp[v][0] == dp[v][1]) {
            isUnique[u][0] = false;
        } else if (dp[v][0] > dp[v][1] && !isUnique[v][0]) {
            isUnique[u][0] = false;
        } else if (dp[v][0] < dp[v][1] && !isUnique[v][1]) {
            isUnique[u][0] = false;
        }
    }
    if (dp[u][0] == dp[u][1]) { return {dp[u][0], false}; }
    if (dp[u][0] > dp[u][1]) { return {dp[u][0], isUnique[u][0]}; }
    return {dp[u][1], isUnique[u][1]};
}

int main() {
    ios::sync_with_stdio(false);
    int n, cnt;
    string root, u, v;
    map<string, int> id;
    vector<vector<int>> g, dp;
    vector<vector<bool>> isUnique;
    while (cin >> n && n != 0) {
        cin >> root;
        cnt = 0;
        id.clear();
        id[root] = cnt++;
        g.clear();
        g.resize(n);
        for (int i = 0; i < n - 1; i++) {
            cin >> u >> v;
            if (id.count(u) == 0) { id[u] = cnt++; }
            if (id.count(v) == 0) { id[v] = cnt++; }
            g[id[v]].push_back(id[u]);
        }
        dp.clear();
        dp.resize(n);
        isUnique.clear();
        isUnique.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(2);
            isUnique[i].resize(2);
        }
        pair<int, bool> ans = dfs(0, dp, isUnique, g);
        cout << ans.first << " " << (ans.second ? "Yes" : "No") << endl;
    }
    return 0;
}
