#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;
constexpr int MAXM = 1e5 + 10;

int n, m, q, ecnt, cnt, u, v;
int h[MAXN], val[MAXN][20], depth[MAXN], parent[MAXN][20], head[MAXN];

struct Graph
{
    int to, w, nex;
} es[MAXN << 1];

struct Edge
{
    int u, v, w;
} edge[MAXM];

void addEdge(int u, int v, int w)
{
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b)
{
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

void dfs(int u, int par, int w)
{
    depth[u] = depth[par] + 1;
    parent[u][0] = par;
    val[u][0] = w;
    for (int j = 1; j < 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
        val[u][j] = max(val[u][j - 1], val[parent[u][j - 1]][j - 1]);
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dfs(v, u, es[i].w);
    }
}

int query(int a, int b)
{
    if (depth[a] > depth[b]) { swap(a, b); }
    int res = 0;
    for (int j = 19; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        res = max(res, val[b][j]);
        b = parent[b][j];
    }
    if (a == b) { return res; }
    for (int j = 19; j >= 0; j--) {
        if (parent[b][j] == parent[a][j]) { continue; }
        res = max({res, val[a][j], val[b][j]});
        a = parent[a][j];
        b = parent[b][j];
    }
    res = max({res, val[a][0], val[b][0]});
    return res;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + 1 + m, [] (const auto &a, const auto &b) { return a.w < b.w; });
    for (int i = 0; i < m; i++) {
        if (same(edge[i].u, edge[i].v)) { continue; }
        join(edge[i].u, edge[i].v);
        addEdge(edge[i].u, edge[i].v, edge[i].w);
        addEdge(edge[i].v, edge[i].u, edge[i].w);
        cnt++;
        if (cnt == n - 1) { break; }
    }
    depth[0] = -1;
    for (int i = 1; i <= n; i++) {
        if (depth[i] != 0) { continue; }
        dfs(i, 0, 0);
    }
    for (int i = 0; i < q; i++) {
        cin >> u >> v;
        if (!same(u, v) || u == v) { cout << "-1" << endl; }
        else { cout << query(u, v) << endl; }
    }
	return 0;
}
