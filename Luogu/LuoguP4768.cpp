// problem statement: https://www.luogu.com.cn/problem/P4768
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;
constexpr int MAXM = 4e5 + 10;

int T, n, m, q, ecnt, cnt, ans, k, s, v0, p0, v, p;
int h[MAXN << 1], head[MAXN << 1], dis[MAXN << 1], depth[MAXN << 1], value[MAXN << 1][21], parent[MAXN << 1][21], val[MAXN << 1];

struct Edge
{
    int u, v, l, a;
} edge[MAXM];

struct Graph
{
    int to, nex, w;
} es[MAXM << 1];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

void addEdge(int u, int v, int w)
{
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void dijkstra()
{
    memset(dis + 1, 0x3f, sizeof(int) * (2 * n - 1));
    dis[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 1});
    vector<bool> used(n + 1, false);
    while (!q.empty()) {
        auto item = q.top();
        q.pop();
        int u = item.second;
        if (used[u]) { continue; }
        used[u] = true;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (dis[v] > dis[u] + es[i].w) {
                dis[v] = dis[u] + es[i].w;
                q.push({dis[v], v});
            }
        }
    }
}

void dfs(int u, int par)
{
    depth[u] = depth[par] + 1;
    parent[u][0] = par;
    value[u][0] = min(val[u], val[par]);
    for (int j = 1; j <= 20; j++) {
        parent[u][j] = parent[parent[u][j - 1]][j - 1];
        value[u][j] = min(value[u][j - 1], value[parent[u][j - 1]][j - 1]);
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dfs(v, u);
        dis[u] = min(dis[u] , dis[v]);
    }
}

int query(int u, int limit)
{
    int now = parent[u][0];
    for (int j = 20; j >= 0; j--) {
        if (value[now][j] <= limit) { continue; }
        now = parent[now][j];
    }
    if (val[now] <= limit) { return dis[u]; }
    return dis[now];
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        ecnt = 0;
        memset(head + 1, -1, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> edge[i].u >> edge[i].v >> edge[i].l >> edge[i].a;
            addEdge(edge[i].u, edge[i].v, edge[i].l);
            addEdge(edge[i].v, edge[i].u, edge[i].l);
        }
        dijkstra();
        ecnt = 0;
        memset(head + 1, -1, sizeof(int) * (2 * n - 1));
        for (int i = 0; i <= 2 * n; i++) { h[i] = i; }
        sort(edge, edge + m, [] (const auto &a, const auto &b) { return a.a > b.a; });
        cnt = n;
        for (int i = 0; i < m; i++) {
            int fu = find(edge[i].u), fv = find(edge[i].v);
            if (fu == fv) { continue; }
            cnt ++;
            h[fu] = h[fv] = cnt;
            addEdge(fu, cnt, 0);
            addEdge(cnt, fu, 0);
            addEdge(fv, cnt, 0);
            addEdge(cnt, fv, 0);
            val[cnt] = edge[i].a;
            if (cnt == 2 * n - 1) { break; }
        }
        depth[0] = -1;
        dfs(cnt, 0);
        ans = 0;
        cin >> q >> k >> s;
        for (int i = 0; i < q; i++) {
            cin >> v0 >> p0;
            v = (v0 + k * ans - 1) % n + 1;
            p = (p0 + k * ans) % (s + 1);
            cout << (ans = query(v, p)) << endl;
        }
    }
	return 0;
}
