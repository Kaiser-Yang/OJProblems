// problem statement: https://www.luogu.com.cn/problem/P3225

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;
constexpr int MAXM = 510;

int n, m, kase, ans1, ecnt, cnt, nodeCnt, cutNodeCnt;
int head[MAXN], u[MAXM], v[MAXM], low[MAXN], dfn[MAXN], vis[MAXN];
bool cut[MAXN];
long long ans2;

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

void tarjan(int u, int par) 
{
    int son = 0;
    dfn[u] = low[u] = ++cnt;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
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

void dfs(int u)
{
    vis[u] = cnt;
    nodeCnt++;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (cut[v] || vis[v] != 0) {
            if (cut[v] && vis[v] != cnt) {
                vis[v] = cnt; 
                cutNodeCnt++;
            }
            continue;
        }
        dfs(v);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    while (cin >> m && m != 0) {
        n = 0;
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i];
            n = max({n, u[i], v[i]});
        }
        ecnt = 0;
        memset(head + 1, 0xff, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            addEdge(u[i], v[i]);
            addEdge(v[i], u[i]);
        }
        cnt = 0;
        memset(cut + 1, 0x00, sizeof(int) * n);
        memset(dfn + 1, 0x00, sizeof(int) * n);
        memset(low + 1, 0x00, sizeof(int) * n);
        tarjan(1, 0);
        cnt = 0;
        ans1 = 0;
        ans2 = 1;
        memset(vis + 1, 0x00, sizeof(int) * n);
        for (int i = 1; i <= n; i++) {
            if (vis[i] != 0 || cut[i]) { continue; }
            cnt++;
            nodeCnt = cutNodeCnt = 0;
            dfs(i);
            if (cutNodeCnt == 0) {
                ans1 += 2;
                ans2 *= 1LL * nodeCnt * (nodeCnt - 1) / 2;
            } else if (cutNodeCnt == 1) { 
                ans1 += 1;
                ans2 *= nodeCnt;
            }
        }
        kase++;
        cout << "Case " << kase << ": ";
        cout << ans1 << " " << ans2 << endl;
    }
	return 0;
}
