// problem statement: https://codeforces.com/contest/839/problem/C

#include <bits/stdc++.h>

using namespace std;

int n, u, v;
double ans;
vector<vector<int>> g;

void dfs(int u, int fa, int len, double probability) {
    for (int v : g[u]) {
        if (v == fa) { continue; }
        dfs(v, u, len + 1, probability / (g[u].size() - (fa != 0)));
    }
    if (g[u].size() == 1) { ans += len * probability; }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    g.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0, 0, 1);
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
