// problem statement: https://www.luogu.com.cn/problem/P1361

#include <bits/stdc++.h>

constexpr int MAXN = 1e3 + 10;
constexpr int MAXM = 1e3 + 10;
constexpr int  INF = std::numeric_limits<int>::max();

using namespace std;

int n, m, s, t, a, b, ans, k, c1, c2, node, ecnt;
int head[MAXN + (MAXM << 1)], cur[MAXN + (MAXM << 1)], depth[MAXN + (MAXM << 1)];

struct Graph
{
    int to, nex, capacity;
} es[(MAXN << 2) + (MAXM << 2) + (MAXM * MAXN << 2)];

void addEdge(int u, int v, int w)
{
    es[ecnt] = {v, head[u], w};
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
        if (depth[v] != depth[u] + 1 || es[i].capacity == 0) { continue; }
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
    cin >> n;
    s = 0, t = n + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        ans += a;
        addEdge(s, i, a);
        addEdge(i, s, 0);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b;
        ans += b;
        addEdge(i, t, b);
        addEdge(t, i, 0);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> k >> c1 >> c2;
        ans += c1 + c2;
        int u = n + 1 + i, v = u + m;
        addEdge(s, u, c1);
        addEdge(u, s, 0);
        addEdge(v, t, c2);
        addEdge(t, v, 0);
        for (int j = 0; j < k; j++) {
            cin >> node;
            addEdge(u, node, INF);
            addEdge(node, u, 0);
            addEdge(node, v, INF);
            addEdge(v, node, 0);
        }
    }
    cout << ans - dinic() << "\n";
	return 0;
}
