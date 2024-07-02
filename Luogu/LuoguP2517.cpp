// problem statement: https://www.luogu.com.cn/problem/P2517

#include <bits/stdc++.h>

constexpr int MAXN = 50 + 10;
constexpr int MAXM = 10 + 5;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, capacity, ecnt, s, t;
int head[MAXN], cur[MAXN], dis[MAXN], need[MAXN], cost[MAXN];
bool vis[MAXN];

struct Graph {
    int to, nex, capacity, cost;
} es[6 * MAXN];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    inq[s] = true;
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity > 0 && dis[v] > dis[u] + es[i].cost) {
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

int dfs(int u, int inFlow, pair<int, int> &ans) {
    if (u == t || inFlow == 0) { return inFlow; }
    int outFlow = 0;
    vis[u]      = true;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(inFlow - outFlow, es[i].capacity), ans);
        if (delta > 0) {
            outFlow += delta;
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            if (inFlow == outFlow) { break; }
        }
    }
    vis[u] = false;
    return outFlow;
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
    memset(head, 0xff, sizeof(head));
    cin >> n >> m >> capacity;
    s = 0, t = n + 1;
    for (int i = 1; i <= n; i++) { cin >> need[i]; }
    for (int i = 1; i <= n; i++) { cin >> cost[i]; }
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, INF, cost[i]);
        addEdge(i, s, 0, -cost[i]);

        addEdge(i, t, need[i], 0);
        addEdge(t, i, 0, 0);

        if (i == n) { continue; }

        addEdge(i, i + 1, capacity, m);
        addEdge(i + 1, i, 0, -m);
    }
    cout << MCMFDinic().second << "\n";
    return 0;
}
