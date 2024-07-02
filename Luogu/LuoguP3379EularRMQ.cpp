// problem statement:

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 10;
const int MAXM = 5e5 + 10;

int n, m, s, u, v, cnt;
int nodeId[MAXN << 1], in[MAXN], depth[MAXN << 1];
int st[MAXN << 1][21], stId[MAXN << 1][21],
    lg[MAXN << 1];  // The eular sequence has 2 * n - 1 nodes.

vector<int> g[MAXN];  // tree

void dfs(int u, int depth) {
    nodeId[++cnt] = u;
    ::depth[cnt]  = depth;
    in[u]         = cnt;
    for (int v : g[u]) {
        if (in[v]) { continue; }
        dfs(v, depth + 1);
        nodeId[++cnt] = u;
        ::depth[cnt]  = depth;
    }
}

void sparseTableInit() {
    for (int i = 2; i <= 2 * n - 1; i++) { lg[i] = lg[i >> 1] + 1; }
    for (int i = 1; i <= 2 * n - 1; i++) { st[i][0] = depth[i], stId[i][0] = nodeId[i]; }
    for (int j = 1; j <= lg[2 * n - 1]; j++) {
        for (int i = 1; i + (1 << j) - 1 <= 2 * n - 1; i++) {
            if (st[i][j - 1] < st[i + (1 << (j - 1))][j - 1]) {
                st[i][j]   = st[i][j - 1];
                stId[i][j] = stId[i][j - 1];
            } else {
                st[i][j]   = st[i + (1 << (j - 1))][j - 1];
                stId[i][j] = stId[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if (in[a] > in[b]) { swap(a, b); }
    int l = in[a], r = in[b];
    int j = lg[r - l + 1];
    return st[l][j] < st[r - (1 << j) + 1][j] ? stId[l][j] : stId[r - (1 << j) + 1][j];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[0] = -1;
    dfs(s, 0);
    sparseTableInit();
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
    return 0;
}
