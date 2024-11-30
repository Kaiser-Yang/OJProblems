// problem statement: https://codeforces.com/contest/2027/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<long long> a;
vector<vector<int>> g;
map<long long, int> id;
map<int, long long> val;
map<int, bool> vis;

void add_edge(long long u, long long v) {
    if (id.count(u) == 0) { id[u] = id.size(); }
    if (id.count(v) == 0) { id[v] = id.size(); }
    val[id[u]] = u;
    val[id[v]] = v;
    g[id[u]].push_back(id[v]);
}

long long dfs(int u) {
    vis[u] = true;
    long long res = val[u];
    for (int v : g[u]) {
        if (vis[v]) { continue; }
        res = max(res, dfs(v));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        id.clear();
        vis.clear();
        g.clear();
        g.resize(2 * n);
        for (int i = 1; i < n; i++) { add_edge(a[i] + i, a[i] + i + i); }
        if (id.count(n) == 0) {
            cout << n << '\n';
        } else {
            cout << dfs(id[n]) << '\n';
        }
    }
    return 0;
}
