// problem statement: http://poj.org/problem?id=2117
// Tag: having been in my blog

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e4 + 10;

int n, m, u, v, cnt, ans, scc;
int dfn[MAXN], low[MAXN];

vector<int> g[MAXN];

void tarjan(int u, int par) {
    dfn[u] = low[u] = ++cnt;
    int son = 0;  // how many sons cannot go to ancestors who are older than their father.
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (dfn[v] == 0) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) { son++; }
        } else if (v != par) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    ans = max(ans, son + (par == 0 ? -1 : 0));
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        if (n == 0 && m == 0) { break; }
        memset(dfn + 1, 0, sizeof(int) * n);
        memset(low + 1, 0, sizeof(int) * n);
        scc = 0;
        ans = -1;
        cnt = 0;
        for (int i = 1; i <= n; i++) { g[i].clear(); }
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            u++;
            v++;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) {
            if (dfn[i] != 0) { continue; }
            scc++;
            tarjan(i, 0);
        }
        cout << ans + scc << endl;
    }
    return 0;
}
