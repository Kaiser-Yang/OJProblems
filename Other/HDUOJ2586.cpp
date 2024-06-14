// problem statement: https://vjudge.net/problem/HDU-2586
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 4e4 + 10;

int n, m, u, v, w, ecnt, T;
int head[MAXN], parent[MAXN][20], dis[MAXN], depth[MAXN];

struct Edge
{
    int to, nex, w;
} es[MAXN << 1];

void addEdge(int u, int v, int w)
{
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void dfs(int u, int par)
{
    parent[u][0] = par;
    depth[u] = depth[par] + 1;
    for (int j = 1; j < 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dis[v] = dis[u] + es[i].w;
        dfs(v, u);
    }
}

int lca(int a, int b)
{
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

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        ecnt = 0;
        memset(head, -1, sizeof(int) * (n + 1));
        for (int i = 1; i < n; i++) {
            cin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        depth[0] = -1;
        dis[1] = 0;
        dfs(1, 0);
        int lca = 0;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            lca = ::lca(u, v);
            cout << dis[u] +  dis[v] - 2 * dis[lca] << endl;
        }
    }
	return 0;
}
