// problem statement: https://loj.ac/p/10091
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;
constexpr int MAXM = 5e4 + 10;

int n, m, u, v, colorCnt, cnt, ans;
int color[MAXN], dfn[MAXN], low[MAXN], dp[MAXN], inDegree[MAXN];
bool ins[MAXN];

stack<int> s;

vector<int> g[MAXN], dag[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    ins[u]          = true;
    s.push(u);
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        colorCnt++;
        while (s.top() != u) {
            color[s.top()] = colorCnt;
            ins[s.top()]   = false;
            s.pop();
        }
        color[s.top()] = colorCnt;
        ins[s.top()]   = false;
        s.pop();
    }
}

void toposort() {
    queue<int> q;
    for (int i = 1; i <= colorCnt; i++) {
        dp[i] = 1;
        if (inDegree[i] == 0) { q.push(i); }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : dag[u]) {
            dp[v] += dp[u];
            if ((--inDegree[v]) == 0) { q.push(v); }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] != 0) { continue; }
        tarjan(i);
    }
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (color[u] == color[v]) { continue; }
            dag[color[u]].push_back(color[v]);
            inDegree[color[v]]++;
        }
    }
    toposort();
    for (int i = 1; i <= n; i++) {
        if (dp[color[i]] == colorCnt) { ans++; }
    }
    cout << ans << endl;
    return 0;
}
