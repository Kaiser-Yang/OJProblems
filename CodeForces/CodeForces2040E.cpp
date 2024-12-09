// problem statement: https://codeforces.com/problemset/problem/2040/E

#include <bits/stdc++.h>

using namespace std;

int T, n, q;
vector<vector<int>> g;
vector<int> par, depth;

void dfs(int u) {
    for (int v : g[u]) {
        if (v == par[u]) { continue; }
        par[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> q;
        g.clear();
        g.resize(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        par.clear();
        par.resize(n + 1);
        depth.clear();
        depth.resize(n + 1);
        dfs(1);
        while (q--) {
            int v, c;
            cin >> v >> c;
            int ans = depth[v];
            vector<int> cnt(n);
            for (int x = par[v]; x > 1; x = par[par[x]]) {
                cnt[g[x].size()]++;
                ans += 2 * (g[x].size() - 1);
            }
            for (int d = n - 1; d > 0 && c > 0; d--) {
                while (cnt[d] > 0 && c > 0) {
                    cnt[d]--;
                    c--;
                    ans -= 2 * (d - 1);
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
