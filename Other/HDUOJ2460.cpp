// problem statement: https://vjudge.net/problem/HDU-2460
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, u, v, ecnt, cnt, q, kase, totBridge;
int head[MAXN], dfn[MAXN], low[MAXN], depth[MAXN], parent[MAXN];
bool bridge[MAXN];

struct Graph
{
    int to, nex;
} es[MAXM << 1];

void addEdge(int u, int v)
{
    es[ecnt].to = v;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void tarjan(const int &u, const int &par, const int &fromEdgeNumber)
{
    dfn[u] = low[u] = ++cnt;
    parent[u] = par;
    depth[u] = depth[par] + 1;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (dfn[v] == 0) {
            tarjan(v, u, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) { 
                bridge[v] = true; 
                totBridge++;
            }
        } else if (fromEdgeNumber == -1 || (i ^ 1) != fromEdgeNumber) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int query(int a, int b) 
{
    int res = 0;
    if (depth[a] > depth[b]) { swap(a, b); }
    while (depth[b] > depth[a]) {
        res += bridge[b];
        bridge[b] = false;
        b = parent[b];
    }
    if (a == b) { return res; }
    while (parent[a] != parent[b]) {
        res += bridge[a] + bridge[b];
        bridge[a] = bridge[b] = false;
        a = parent[a];
        b = parent[b];
    }
    res += bridge[a] + bridge[b];
    bridge[a] = bridge[b] = false;
    return res;
}

int main()
{
	ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        if (n == 0 && m == 0) { break; }
        ecnt = 0;
        cnt = 0;
        totBridge = 0;
        memset(dfn + 1, 0x00, sizeof(int) * n);
        memset(low + 1, 0x00, sizeof(int) * n);
        memset(head + 1, 0xff, sizeof(int) * n);
        memset(bridge + 1, 0x00, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        depth[0] = -1;
        tarjan(1, 0, -1);
        kase++;
        cout << "Case " << kase << ":\n";
        cin >> q;
        for (int i = 0; i < q; i++) {
            cin >> u >> v;
            totBridge -= query(u, v);
            cout << totBridge << endl;
        }
        cout << endl;
    }
	return 0;
}
