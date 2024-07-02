// problem statement: https://www.luogu.com.cn/problem/P4180
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 3e5 + 10;

int n, m, cnt, ecnt;
long long ans = numeric_limits<long long>::max(), mst;
int h[MAXN], parent[MAXN][20], depth[MAXN], head[MAXN], maxValue[MAXN][20], subMaxValue[MAXN][20];

struct Graph {
    int to, w, nex;
} es[MAXN << 1];

struct Edge {
    int u, v, w;
    bool added = false;
} edge[MAXM];

void addEdge(int u, int v, int w) {
    es[ecnt].to  = v;
    es[ecnt].w   = w;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

void dfs(int u, int par, int w) {
    depth[u]          = depth[par] + 1;
    parent[u][0]      = par;
    maxValue[u][0]    = w;
    subMaxValue[u][0] = -1;
    for (int j = 1; j < 20; j++) {
        parent[u][j]      = parent[parent[u][j - 1]][j - 1];
        subMaxValue[u][j] = max(subMaxValue[u][j - 1], subMaxValue[parent[u][j - 1]][j - 1]);
        if (maxValue[parent[u][j - 1]][j - 1] > maxValue[u][j - 1] &&
            maxValue[u][j - 1] > subMaxValue[u][j]) {
            subMaxValue[u][j] = maxValue[u][j - 1];

        } else if (maxValue[u][j - 1] > maxValue[parent[u][j - 1]][j - 1] &&
                   maxValue[parent[u][j - 1]][j - 1] > subMaxValue[u][j]) {
            subMaxValue[u][j] = maxValue[parent[u][j - 1]][j - 1];
        }
        maxValue[u][j] = max(maxValue[u][j - 1], maxValue[parent[u][j - 1]][j - 1]);
    }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        dfs(v, u, es[i].w);
    }
}

pair<int, int> query(int a, int b) {
    int res1 = -1, res2 = -1;
    if (depth[a] > depth[b]) { swap(a, b); }
    for (int j = 19; j >= 0; j--) {
        if (depth[parent[b][j]] < depth[a]) { continue; }
        res2 = max(res2, subMaxValue[b][j]);
        if (maxValue[b][j] > res1 && res1 > res2) {
            res2 = res1;
        } else if (res1 > maxValue[b][j] && maxValue[b][j] > res2) {
            res2 = maxValue[b][j];
        }
        res1 = max(res1, maxValue[b][j]);
        b    = parent[b][j];
    }
    if (a == b) { return {res1, res2}; }
    int temp = 0;
    for (int j = 19; j >= 0; j--) {
        if (parent[a][j] == parent[b][j]) { continue; }
        res2 = max({res2, subMaxValue[a][j], subMaxValue[b][j]});
        temp = max(maxValue[a][j], maxValue[b][j]);
        if (temp > res1 && res1 > res2) {
            res2 = res1;
        } else if (res1 > temp && temp > res2) {
            res2 = temp;
        }
        res1 = max({res1, temp});
        a    = parent[a][j];
        b    = parent[b][j];
    }
    res2 = max({res2, subMaxValue[a][0], subMaxValue[b][0]});
    temp = max(maxValue[a][0], maxValue[b][0]);
    if (temp > res1 && res1 > res2) {
        res2 = res1;
    } else if (res1 > temp && temp > res2) {
        res2 = temp;
    }
    res1 = max({res1, maxValue[a][0], maxValue[b][0]});
    return {res1, res2};
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [](const auto &a, const auto &b) { return a.w < b.w; });
    for (int i = 0; i < m; i++) {
        if (!same(edge[i].u, edge[i].v)) {
            cnt++;
            join(edge[i].u, edge[i].v);
            edge[i].added = true;
            mst += edge[i].w;
            addEdge(edge[i].u, edge[i].v, edge[i].w);
            addEdge(edge[i].v, edge[i].u, edge[i].w);
        }
        if (cnt == n - 1) { break; }
    }
    depth[0] = -1;
    dfs(1, 0, 0);
    for (int i = 0; i < m; i++) {
        if (edge[i].added) { continue; }
        auto res = query(edge[i].u, edge[i].v);
        if (res.first == -1) {
            continue;
        } else if (res.first != edge[i].w) {
            ans = min(ans, mst - res.first + edge[i].w);
        } else if (res.second != -1) {
            ans = min(ans, mst - res.second + edge[i].w);
        }
    }
    cout << ans << endl;
    return 0;
}
