// problem statement: https://www.luogu.com.cn/problem/P2764

#include <bits/stdc++.h>

constexpr int MAXN = 150 + 5;
constexpr int MAXM = 6000 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, ans;
vector<pair<int, int>> edge;
int s, t, ecnt;
int head[2 * MAXN], cur[2 * MAXN], depth[2 * MAXN], h[MAXN];
bool vis[2 * MAXN];
vector<int> path, g[MAXN];

struct Graph {
    int to, nex, capacity;
} es[MAXM * 2 + 4 * MAXN];

void addEdge(int u, int v, int w) {
    es[ecnt].to       = v;
    es[ecnt].capacity = w;
    es[ecnt].nex      = head[u];
    head[u]           = ecnt++;
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

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

void dfs(int u) {
    for (int i = head[u]; i != -1; i = es[i].nex) {
        if (i % 2 == 1 || es[i].capacity > 0 || es[i].to == t) { continue; }
        int v = es[i].to;
        if (v > n) { v -= n; }
        if (u != s) { join(u, v); }
        dfs(v);
    }
}

int findPath(int u) {
    path.push_back(u);
    for (const int &v : g[u]) {
        if (find(v) != find(u)) { continue; }
        return findPath(v) + 1;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    edge.resize(m);
    for (int i = 0; i < m; i++) { cin >> edge[i].first >> edge[i].second; }
    s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, 1);
        addEdge(i, s, 0);
        addEdge(i + n, t, 1);
        addEdge(t, i + n, 0);
    }
    for (int i = 0; i < m; i++) {
        addEdge(edge[i].first, edge[i].second + n, 1);
        addEdge(edge[i].second + n, edge[i].first, 0);
        g[edge[i].first].push_back(edge[i].second);
    }
    ans = n - dinic();
    dfs(s);
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) {
            int cnt = 0;
            for (int j = 1; j <= n; j++) { cnt += same(i, j); }
            for (int j = 1; j <= n; j++) {
                path.clear();
                if (!same(i, j) || findPath(j) != cnt) { continue; }
                for (const int &id : path) { cout << id << " "; }
                cout << "\n";
                break;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
