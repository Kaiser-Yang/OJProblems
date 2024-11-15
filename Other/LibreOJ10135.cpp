// problem statement: https://loj.ac/p/10135
//  Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 4e4 + 10;

int n, m, u, v, root;
int depth[MAXN], parent[MAXN][20];

vector<int> g[MAXN];

void dfs(int u, int par) {
    parent[u][0] = par;
    depth[u] = depth[par] + 1;
    for (int j = 1; j < 20; j++) { parent[u][j] = parent[parent[u][j - 1]][j - 1]; }
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) { swap(a, b); }
    for (int j = 19; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        b = parent[b][j];
    }
    if (a == b) { return a; }
    for (int j = 19; j >= 0; j--) {
        if (parent[a][j] == parent[b][j]) { continue; }
        a = parent[a][j];
        b = parent[b][j];
    }
    return parent[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> u >> v;
        if (v == -1) {
            root = u;
            continue;
        }
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[0] = -1;
    dfs(root, 0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        int lca = ::lca(u, v);
        if (lca == u) {
            cout << "1\n";
        } else if (lca == v) {
            cout << "2\n";
        } else {
            cout << "0\n";
        }
    }
    return 0;
}
