// problem statement: https://www.luogu.com.cn/problem/P4779
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, s, u, v, w;
int dis[MAXN];

struct Edge
{
    int to, w;
};

vector<Edge> g[MAXN];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    vector<bool> used(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    dis[s] = 0;
    while (!q.empty()) {
        auto item = q.top();
        q.pop();
        int u = item.second;
        if (used[u]) { continue; }
        used[u] = true;
        for (auto edge : g[u]) {
            int v = edge.to, w = edge.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++) { cout << dis[i] << " "; }
    cout << endl;
	return 0;
}
