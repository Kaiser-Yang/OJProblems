// problem statement: https://www.luogu.com.cn/problem/P2057

#include <bits/stdc++.h>

constexpr int MAXN = 310;
constexpr int MAXM = MAXN * MAXN / 2;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, m, u, v, s, t, ecnt;
bool willing[MAXN];
int head[MAXN], cur[MAXN], depth[MAXN];

struct Graph
{
    int to, nex, capacity;
}es[(MAXM << 2) + (MAXN << 1)];

void addEdge(int u, int v, int w)
{
    es[ecnt].to = v;
    es[ecnt].capacity = w;
    es[ecnt].nex =head[u];
    head[u] = ecnt++;
}

bool bfs()
{
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (depth[v] != 0 || es[i].capacity == 0) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != 0;
}

int dfs(int u, int flow)
{
    if (u == t || flow == 0) { return flow; }
    int res = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (depth[v] != depth[u] + 1) { continue; }
        int outFlowV = dfs(v, min(flow - res, es[i].capacity));
        if (outFlowV > 0) {
            res += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            if (res == flow) { return res; }
        }
    }
    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    s = 0, t = n + 1;
    for (int i = 1; i <= n; i++) { cin >> willing[i]; }
    for (int i = 1; i <= n; i++) {
        if (!willing[i]) {
            addEdge(i, t, 1);
            addEdge(t, i , 0);
        } else {
            addEdge(s, i, 1);
            addEdge(i, s, 0);
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        addEdge(u, v, 1);
        addEdge(v, u, 0);
        addEdge(v, u, 1);
        addEdge(u, v, 0);
    }
    cout << dinic() << "\n";
	return 0;
}
