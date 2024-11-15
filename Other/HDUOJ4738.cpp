// problem statement: https://vjudge.net/problem/HDU-4738
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;

int n, m, u, v, w, cnt, siz, ans, ecnt;
int dfn[MAXN], low[MAXN], head[MAXN];

struct Graph {
    int to, nex, w;
} es[MAXN * MAXN * 2];

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void tarjan(int u, int lastEdgeNumber) {
    siz++;
    dfn[u] = low[u] = ++cnt;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to, w = es[i].w;
        if (dfn[v] == 0) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) { ans = min(ans, w); }
        } else if (lastEdgeNumber == -1 || (lastEdgeNumber ^ 1) != i) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        if (n == 0 && m == 0) { break; }
        ecnt = 0;
        cnt = 0;
        siz = 0;  // the scc size from node 1.
        ans = numeric_limits<int>::max();
        memset(dfn + 1, 0, sizeof(int) * n);
        memset(low + 1, 0, sizeof(int) * n);
        memset(head + 1, -1, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        tarjan(1, -1);
        if (siz != n) {
            cout << "0\n";
        } else if (ans == numeric_limits<int>::max()) {
            cout << "-1\n";
        } else if (ans == 0) {
            cout << "1\n";
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
