// problem statement: http://poj.org/problem?id=1523
// Tag: having been in my blog

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

int kase, u, v, n, cnt, cutNodeCnt;
int cut[MAXN], dfn[MAXN], low[MAXN];

bool g[MAXN][MAXN];

vector<pair<int, int> > edge;

void tarjan(int u, int par)
{
    dfn[u] = low[u] = ++cnt;
    int son = 0;
    for (int v = 1; v <= n; v++) {
        if (!g[u][v]) { continue; }
        if (dfn[v] == 0) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) { son++; }
        } else if (v != par) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    cut[u] = son;
    if (par != 0 && cut[u] > 0) { cut[u]++; }
    if (par == 0 && cut[u] <= 1) { cut[u] = 0; }
}

int main()
{
	ios::sync_with_stdio(false);
    while (cin >> u) {
        if (u == 0) { break; }
        edge.clear();
        n = 0;
        n = max(n, u);
        do {
            cin >> v;
            edge.push_back(pair<int, int>(u, v));
            n = max(n, v);
        } while (cin >> u && u != 0);
        memset(dfn + 1, 0x00, sizeof(int) * n);
        memset(low + 1, 0x00, sizeof(int) * n);
        memset(cut + 1, 0x00, sizeof(int) * n);
        for (int i = 1; i <= n; i++) { memset(g + i, 0, sizeof(bool) * (n + 1)); }
        for (int i = 0; i < edge.size(); i++) {
            u = edge[i].first, v = edge[i].second;
            g[u][v] = g[v][u] = true;
        }
        cutNodeCnt = 0;
        cnt = 0;
        tarjan(1, 0);
        kase++;
        cout << "Network #" << kase << endl;
        for (int i = 1; i <= n; i++) {
            if (cut[i] > 0) { cutNodeCnt++; }
        }
        if (cutNodeCnt == 0) { cout << "  No SPF nodes\n"; }
        else {
            for (int i = 1; i <= n; i++) {
                if (cut[i] > 0) { cout << "  SPF node " << i << " leaves " << cut[i] << " subnets\n"; }
            }
        }
        cout << endl;
    }
	return 0;
}
