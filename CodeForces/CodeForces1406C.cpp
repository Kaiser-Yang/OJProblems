// problem statement: https://codeforces.com/problemset/problem/1406/C
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int T, n, u, v, fathest, fathestParent;
int siz[MAXN], depth[MAXN];

vector<int> g[MAXN], centroid;

void dfs(int u, int par) {
    siz[u]         = 1;
    int maxSonSize = 0;
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
        siz[u] += siz[v];
        maxSonSize = max(maxSonSize, siz[v]);
    }
    if (maxSonSize <= n / 2 && n - siz[u] <= n / 2) { centroid.push_back(u); }
}

void fathestNode(int u, int par) {
    depth[u] = depth[par] + 1;
    if (depth[u] > depth[fathest]) {
        fathest       = u;
        fathestParent = par;
    }
    for (int v : g[u]) {
        if (v == par || v == centroid[1]) { continue; }
        fathestNode(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for_each(g, g + 1 + n, [](auto &v) { v.clear(); });
        centroid.clear();
        for (int i = 1; i < n; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        if (centroid.size() == 1) {
            cout << u << " " << v << endl;
            cout << u << " " << v << endl;
            continue;
        }
        depth[0] = -1;
        fathest = fathestParent = 0;
        fathestNode(centroid[0], 0);
        cout << fathest << " " << fathestParent << endl;
        cout << fathest << " " << centroid[1] << endl;
    }
    return 0;
}
