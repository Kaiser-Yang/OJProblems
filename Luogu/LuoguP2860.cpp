// problem statement: https://www.luogu.com.cn/problem/P2860
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e3 + 10;
constexpr int MAXM = 1e4 + 10;

int n, m, u, v, ecnt, cnt, colorCnt;
int head[MAXN], dfn[MAXN], low[MAXN], color[MAXN], outDegree[MAXN];
bool ins[MAXN], vis[MAXM << 1];

stack<int> s;

struct Graph {
    int to, nex;
} es[MAXM << 1];

void addEdge(int u, int v) {
    es[ecnt].to  = v;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    s.push(u);
    ins[u] = true;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        if (vis[i]) { continue; }
        vis[i] = vis[i ^ 1] = true;
        int v               = es[i].to;
        if (!dfn[v]) {
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

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    tarjan(1);
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i != -1; i = es[i].nex) {
            v = es[i].to;
            if (color[u] == color[v]) { continue; }
            outDegree[color[u]]++;
        }
    }
    cout << ((count_if(outDegree + 1, outDegree + 1 + n, [](auto val) { return val == 1; }) + 1) >>
             1)
         << endl;
    return 0;
}
