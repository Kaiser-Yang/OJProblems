// problem statement: https://www.luogu.com.cn/problem/P4568

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;
constexpr int MAXK = 11;

int n, m, k, s, t, u, v, w, ans = numeric_limits<int>::max();
int dis[MAXN][MAXK];

struct Edge
{
    int to, w;
};

vector<Edge> g[MAXN];

void dijkstra()
{
    vector<vector<bool>> used(n, vector<bool>(k + 1, false));
    memset(dis, 0x3f, sizeof(dis));
    struct State
    {
        int dis, u, cnt;
        bool operator<(const State &other) const { return dis > other.dis; }
    };
    priority_queue<State> q;
    dis[s][0] = 0;
    q.push({0, s, 0});
    while (!q.empty()) {
        auto item = q.top();
        q.pop();
        u = item.u;
        if (used[u][item.cnt]) { continue; }
        used[u][item.cnt] = true;
        for (auto vw : g[u]) {
            v = vw.to, w = vw.w;
            if (item.cnt < k && dis[v][item.cnt + 1] > dis[u][item.cnt]) {
                dis[v][item.cnt + 1] = dis[u][item.cnt];
                q.push({dis[v][item.cnt + 1], v, item.cnt + 1});
            }
            if (dis[v][item.cnt] > dis[u][item.cnt] + w) {
                dis[v][item.cnt] = dis[u][item.cnt] + w;
                q.push({dis[v][item.cnt], v, item.cnt});
            }
        }
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    cin >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dijkstra();
    for (int i = 0; i <= k; i++) { ans = min(ans, dis[t][i]); }
    cout << ans << endl;
	return 0;
}
