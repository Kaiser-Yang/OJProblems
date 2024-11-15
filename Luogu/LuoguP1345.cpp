// problem statement: https://www.luogu.com.cn/problem/P1345

#include <bits/stdc++.h>

constexpr int MAXN = 110;
constexpr int MAXM = 610;
constexpr int INF = 0X3f3f3f3f;

using namespace std;

int n, m, s, t, u, v, ecnt;
int head[MAXN << 1], depth[MAXN << 1], cur[MAXN << 1];

struct Graph {
    int to, nex, capacity;
} es[(MAXM << 2) + (MAXN << 1)];

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].capacity = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

bool bfs() {
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

int dfs(int u, int flow) {
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

int dinic() {
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= n; i++) {
        if (i == s || i == t) { continue; }
        addEdge(i, i + n, 1);
        addEdge(i + n, i, 0);
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        if (u == s || u == t) {
            if (v == s || v == t) {
                continue;
            } else {
                addEdge(u, v, INF);
                addEdge(v, u, 0);
                addEdge(v + n, u, INF);
                addEdge(u, v + n, 0);
            }
        } else {
            if (v == s || v == t) {
                addEdge(u + n, v, INF);
                addEdge(v, u + n, 0);
                addEdge(v, u, INF);
                addEdge(u, v, 0);
            } else {
                addEdge(u + n, v, INF);
                addEdge(v, u + n, 0);
                addEdge(v + n, u, INF);
                addEdge(u, v + n, 0);
            }
        }
    }
    cout << dinic() << endl;
    return 0;
}
