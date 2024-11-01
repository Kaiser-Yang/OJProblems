// problem statement: https://www.luogu.com.cn/problem/P5905
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e3 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, u, v, w;
long long dis[MAXN][MAXN], d[MAXN];

struct Edge {
    int to, w;
};

vector<Edge> g[MAXN];

// return if has negative circle
bool bellmanFord() {
    memset(d, 0x3f, sizeof(d));
    d[0] = 0;
    bool flag = false;
    for (int i = 0; i <= n; i++) {
        flag = false;
        for (int u = 0; u <= n; u++) {
            if (d[u] == INF) { continue; }
            for (auto item : g[u]) {
                int v = item.to, w = item.w;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    flag = true;
                }
            }
        }
        if (!flag) { return false; }
    }
    return flag;
}

void dijkstra(int s, long long *dis) {
    vector<bool> used(n + 1, false);
    memset(dis, 0x3f, sizeof(long long) * (n + 1));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto item = q.top();
        q.pop();
        int u = item.second;
        if (used[u]) { continue; }
        used[u] = true;
        for (auto it : g[u]) {
            int v = it.to, w = it.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}

void johnson() {
    for (int i = 1; i <= n; i++) { g[0].push_back({i, 0}); }
    if (bellmanFord()) {
        cout << "-1" << endl;
        exit(0);
    }
    for (int u = 1; u <= n; u++) {
        for (auto &item : g[u]) {
            int v = item.to;
            item.w += d[u] - d[v];
        }
    }
    for (int i = 1; i <= n; i++) { dijkstra(i, dis[i]); }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dis[i][j] = 0;
            } else if (dis[i][j] == INF) {
                dis[i][j] = 1e9;
            } else {
                dis[i][j] -= d[i] - d[j];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    johnson();
    for (int i = 1; i <= n; i++) {
        long long ans = 0;
        for (int j = 1; j <= n; j++) { ans += j * dis[i][j]; }
        cout << ans << endl;
    }
    return 0;
}
