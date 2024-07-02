// problem statement: https://www.luogu.com.cn/problem/P4452

#include <bits/stdc++.h>

constexpr int MAXN = 200 + 10;
constexpr int MAXM = 200 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, k, endTime, source, sink, ecnt;
int t[MAXN][MAXN], f[MAXN][MAXN], a[MAXM], b[MAXM], start[MAXM], end[MAXM], c[MAXM];
int head[MAXM << 1], cur[MAXM << 1], dis[MAXM << 1];
bool vis[MAXM << 1];

struct Graph {
    int to, nex, capacity, cost;
} es[2 * MAXM * MAXM];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa() {
    for (int i = 0; i <= sink; i++) { dis[i] = -INF; }
    auto &inq = vis;
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    inq[source] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity > 0 && dis[v] < dis[u] + es[i].cost) {
                dis[v] = dis[u] + es[i].cost;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return dis[sink] != -INF;
}

int dfs(int u, int flow, pair<int, int> &ans) {
    if (u == sink || flow == 0) { return flow; }
    int res = 0;
    vis[u]  = true;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int outFlowV = dfs(v, min(flow - res, es[i].capacity), ans);
        if (outFlowV > 0) {
            res += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            ans.second += outFlowV * es[i].cost;
            if (res == flow) { break; }
        }
    }
    vis[u] = false;
    return res;
}

pair<int, int> MCMFDinic() {
    pair<int, int> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        while ((flow = dfs(source, INF, ans)) != 0) ans.first += flow;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> k >> endTime;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cin >> t[i][j]; }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cin >> f[i][j]; }
    }
    source = 2 * m + 5, sink = source + 2;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> start[i] >> ::end[i] >> c[i];
        addEdge(i, i + m, 1, c[i]);
        addEdge(i + m, i, 0, -c[i]);
        if (::end[i] + t[b[i]][0] <= endTime) {
            addEdge(i + m, sink, INF, -f[b[i]][0]);
            addEdge(sink, i + m, 0, f[b[i]][0]);
        } else {
            continue;
        }
        if (t[0][a[i]] <= start[i]) {
            addEdge(source, i, INF, -f[0][a[i]]);
            addEdge(i, source, 0, f[0][a[i]]);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) { continue; }
            if (::end[i] + t[b[i]][a[j]] <= start[j]) {
                addEdge(i + m, j, INF, -f[b[i]][a[j]]);
                addEdge(j, i + m, 0, f[b[i]][a[j]]);
            }
        }
    }
    addEdge(source + 1, source, k, 0);
    addEdge(source, source + 1, 0, 0);
    source++;
    cout << MCMFDinic().second << "\n";
    return 0;
}
