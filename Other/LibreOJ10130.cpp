//problem statement: https://loj.ac/p/10130
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXQ = 1e5 + 10;

int n, q, ecnt, u, v, lca;
int queryHead[MAXQ], depth[MAXN], parent[MAXN];
bool vis[MAXN];

vector<int> g[MAXN];

struct QueryEdge
{
    int from, to, nex, lca;
} queryEdge[MAXQ << 1];

void addQueryEdge(int u, int v)
{
    queryEdge[ecnt].from = u;
    queryEdge[ecnt].to = v;
    queryEdge[ecnt].nex = queryHead[u];
    queryHead[u] = ecnt++;
}

int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

void tarjan(int u)
{
    parent[u] = u;
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) { continue; }
        depth[v] = depth[u] + 1;
        tarjan(v);
        parent[v] = u;
    }
    for (int i = queryHead[u]; i != -1; i = queryEdge[i].nex) {
        int v = queryEdge[i].to;
        if (vis[v]) {
            queryEdge[i].lca = queryEdge[i ^ 1].lca = find(v);
        }
    }
}

int main()
{
	ios::sync_with_stdio(false);
    memset(queryHead, 0xff, sizeof(queryHead));
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> u >> v;
        addQueryEdge(u, v);
        addQueryEdge(v, u);
    }
    tarjan(1);
    for (int i = 0; i < q; i++) {
        u = queryEdge[i * 2].from, v = queryEdge[i * 2].to, lca = queryEdge[i * 2].lca;
        cout << depth[u] + depth[v] - 2 * depth[lca] << endl;
    }
	return 0;
}
