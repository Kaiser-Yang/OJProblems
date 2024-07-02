// problem statement: https://www.luogu.com.cn/problem/P5058
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int n, u, v, s, t, ans = MAXN, cnt;
int dfn[MAXN], low[MAXN];

vector<int> g[MAXN];

void tarjan(int u, int par) {
    dfn[u] = low[u] = ++cnt;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != s && u != t && dfn[v] <= dfn[t]) { ans = min(ans, u); }
        } else if (v != par) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    while (cin >> u >> v) {
        if (u == 0 && v == 0) { break; }
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> s >> t;
    tarjan(s, 0);
    cout << (ans == MAXN ? "No solution" : to_string(ans)) << endl;
    return 0;
}
