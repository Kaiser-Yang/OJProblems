// problem statement: https://www.luogu.com.cn/problem/P3128

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e4 + 10;

int n, k, u, v, s, t, lcaST, ans;

vector<int> g[MAXN];

array<int, MAXN> sum, depth;
array<array<int, 20>, MAXN> par;

int lca(int a, int b) {
    if (depth[a] < depth[b]) { swap(a, b); }
    for (int j = 19; j >= 0; j--) {
        if (depth[par[a][j]] >= depth[b]) { a = par[a][j]; }
    }
    if (a == b) { return a; }
    for (int j = 19; j >= 0; j--) {
        if (par[a][j] != par[b][j]) {
            a = par[a][j];
            b = par[b][j];
        }
    }
    return par[a][0];
}

void dfs(int u, int fa) {
    depth[u] = depth[fa] + 1;
    par[u][0] = fa;
    for (int j = 1; j < 20; j++) { par[u][j] = par[par[u][j - 1]][j - 1]; }
    for (auto &v : g[u]) {
        if (v == fa) { continue; }
        dfs(v, u);
        sum[u] += sum[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[0] = -1;
    dfs(1, 0);
    for (int i = 0; i < k; i++) {
        cin >> s >> t;
        sum[s]++;
        sum[t]++;
        lcaST = lca(s, t);
        sum[lcaST]--;
        sum[par[lcaST][0]]--;
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) { ans = max(ans, sum[i]); }
    cout << ans << "\n";
    return 0;
}
