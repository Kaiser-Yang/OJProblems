// problem statement: https://www.luogu.com.cn/problem/P3381

#include <bits/stdc++.h>

constexpr int MAXN = 5e3 + 10;
constexpr int MAXM = 5e4 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, s, t, u, v, capacity, cost, ecnt;
int head[MAXN], cur[MAXN], dis[MAXN];
bool vis[MAXN];

struct Graph {
    int to, nex, capacity, cost;
} es[MAXM << 1];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity != 0 && dis[v] > dis[u] + es[i].cost) {
                dis[v] = dis[u] + es[i].cost;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int u, int flow, pair<int, int> &ans) {
    if (u == t || flow == 0) { return flow; }
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
        while ((flow = dfs(s, INF, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> capacity >> cost;
        addEdge(u, v, capacity, cost);
        addEdge(v, u, 0, -cost);
    }
    auto ans = MCMFDinic();
    cout << ans.first << " " << ans.second << "\n";
    return 0;
}
