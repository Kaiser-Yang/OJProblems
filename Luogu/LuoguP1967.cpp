// problem statement: https://www.luogu.com.cn/problem/P1967
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;
constexpr int MAXM = 5e4 + 10;

int n, m, ecnt, q, u, v;
int h[MAXN], head[MAXN];
int depth[MAXN], parent[MAXN][20], value[MAXN][20];

struct Edge {
    int u, v, w;
} edge[MAXN];

struct GraphEdge {
    int to, nex, w;
} es[MAXN << 1];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    h[fa]  = fb;
}

void addEdge(int u, int v, int w) {
    es[ecnt].to  = v;
    es[ecnt].w   = w;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

int query(int a, int b) {
    int res = std::numeric_limits<int>::max();
    if (depth[a] > depth[b]) { swap(a, b); }
    for (int j = 19; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        res = min(res, value[b][j]);
        b   = parent[b][j];
    }
    if (a == b) { return res; }
    for (int j = 19; j >= 0; j--) {
        if (parent[a][j] == parent[b][j]) { continue; }
        res = min({res, value[a][j], value[b][j]});
        a   = parent[a][j];
        b   = parent[b][j];
    }
    res = min({res, value[a][0], value[b][0]});
    return res;
}

void dfs(int u, int par, int w) {
    parent[u][0] = par;
    value[u][0]  = w;
    depth[u]     = depth[par] + 1;
    for (int j = 1; j < 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
        value[u][j]  = min(value[u][j - 1], value[parent[u][j - 1]][j - 1]);
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dfs(v, u, es[i].w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [](const Edge &a, const Edge &b) { return a.w > b.w; });
    int cnt = 0;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) {
        if (!same(edge[i].u, edge[i].v)) {
            addEdge(edge[i].u, edge[i].v, edge[i].w);
            addEdge(edge[i].v, edge[i].u, edge[i].w);
            join(edge[i].u, edge[i].v);
            cnt++;
            if (cnt == n - 1) { break; }
        }
    }
    depth[0] = -1;
    for (int i = 1; i <= n; i++) {
        if (depth[i] == 0) { dfs(i, 0, 0); }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> u >> v;
        if (!same(u, v)) {
            cout << "-1\n";
        } else {
            cout << query(u, v) << endl;
        }
    }
    return 0;
}
