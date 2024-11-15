// Timus Online Judge
// Judge ID: 375702TB
// problem statement: https://acm.timus.ru/problem.aspx?space=1&num=1416
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 510;
constexpr int MAXM = MAXN * MAXN;

int n, m, cnt, ecnt, mst, ans = numeric_limits<int>::max();
int h[MAXN], head[MAXN], parent[MAXN][20], depth[MAXN], w[MAXN][20];

struct Graph {
    int to, nex, w;
} es[MAXN << 1];

struct Edge {
    int u, v, w;
    bool added = false;
} edge[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void dfs(int u, int par, int w) {
    depth[u] = depth[par] + 1;
    parent[u][0] = par;
    ::w[u][0] = w;
    for (int j = 1; j < 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
        ::w[u][j] = max(::w[u][j - 1], ::w[parent[u][j - 1]][j - 1]);
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dfs(v, u, es[i].w);
    }
}

int queryMaxEdge(int a, int b) {
    int res = 0;
    if (depth[a] > depth[b]) { swap(a, b); }
    for (int j = 19; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        res = max(res, w[b][j]);
        b = parent[b][j];
    }
    if (a == b) { return res; }
    for (int j = 19; j >= 0; j--) {
        if (parent[a][j] == parent[b][j]) { continue; }
        res = max({res, w[a][j], w[b][j]});
        a = parent[a][j];
        b = parent[b][j];
    }
    res = max({res, w[a][0], w[b][0]});
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [](const auto &a, const auto &b) { return a.w < b.w; });
    for (int i = 0; i < m; i++) {
        if (!same(edge[i].u, edge[i].v)) {
            join(edge[i].u, edge[i].v);
            edge[i].added = true;
            mst += edge[i].w;
            cnt++;
            addEdge(edge[i].u, edge[i].v, edge[i].w);
            addEdge(edge[i].v, edge[i].u, edge[i].w);
        }
        if (cnt == n - 1) { break; }
    }
    if (cnt < n - 1) {
        cout << "Cost: -1" << endl;
        cout << "Cost: -1" << endl;
        return 0;
    }
    depth[0] = -1;
    dfs(1, 0, 0);
    for (int i = 0; i < m; i++) {
        if (edge[i].added) { continue; }
        ans = min(ans, mst - queryMaxEdge(edge[i].u, edge[i].v) + edge[i].w);
    }
    if (ans == numeric_limits<int>::max()) { ans = -1; }
    cout << "Cost: " << mst << endl;
    cout << "Cost: " << ans << endl;
    return 0;
}
