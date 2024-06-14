// problem statement: https://www.luogu.com.cn/problem/P3388
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e4 + 10;

int n, m, u, v, cnt;
int dfn[MAXN], low[MAXN];
bool cut[MAXN];

vector<int> g[MAXN];

void tarjan(int u, int par)
{
    dfn[u] = low[u] = ++cnt;
    int son = 0;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            son++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (par != 0 && low[v] >= dfn[u]) { cut[u] = true; }
        } else if (v != par) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (par == 0 && son >= 2) { cut[u] = true; }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] != 0) { continue; }
        tarjan(i, 0);
    }
    cout << count_if(cut + 1, cut + 1 + n, [] (bool val) { return val; }) << endl;
    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
	return 0;
}
