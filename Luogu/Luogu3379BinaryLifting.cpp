#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 10;
const int MAXM = 5e5 + 10;

int n, m, s, u, v;
int parent[MAXN][21], depth[MAXN];

vector<int> g[MAXN]; // tree

void dfs(int u, int par)
{
    parent[u][0] = par;
    depth[u] = depth[par] + 1;
    for (int j = 1; j <= 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
    }
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    for ( int j = 20; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        b = parent[b][j];
    }
    if (a == b) { return a; }
    for (int j = 20; j >= 0; j--) {
        if (parent[a][j] == parent[b][j]) { continue; }
        a = parent[a][j];
        b = parent[b][j];
    }
    return parent[a][0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[0] = -1;
    dfs(s, 0);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
	return 0;
}
