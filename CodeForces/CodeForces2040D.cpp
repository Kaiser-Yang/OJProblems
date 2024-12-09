// problem statement: https://codeforces.com/contest/2040/problem/D

#include <bits/stdc++.h>

using namespace std;

int T, n, cur;
vector<vector<int>> g;
vector<int> ans;

void dfs(int u, int par) {
    ans[u] = cur;
    bool first = true;
    for (int v : g[u]) {
        if (v == par) { continue; }
        if (first) {
            first = false;
            cur++;
            dfs(v, u);
            cur++;
        } else {
            cur += 2;
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        g.clear();
        g.resize(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        ans.resize(n + 1);
        cur = 1;
        dfs(1, 0);
        for (int i = 1; i <= n; i++) { cout << ans[i] << " \n"[i == n]; }
    }
    return 0;
}
