// problem statement: https://www.luogu.com.cn/problem/P4012

#include <bits/stdc++.h>

constexpr int MAXN = 15 + 5;
constexpr int MAXM = 15 + 5;
constexpr int MAXA = 4 + 2;
constexpr int MAXB = 6 + 2;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int a, b, n, m, cost;
int s, t, ecnt, idCnt;
int id[MAXN][MAXM];
int head[MAXN * MAXM], cur[MAXN * MAXM], dis[MAXN * MAXM];
bool vis[MAXN * MAXM];

struct Graph {
    int to, nex, capacity;
    long long cost;
} es[8 * MAXN * MAXM + 2 * (MAXA + MAXB)];

void addFlow(int u, int v, int capacity, long long cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
    es[ecnt] = {u, head[v], 0, -cost};
    head[v]  = ecnt++;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    q.push(s);
    inq[s] = true;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (dis[v] > dis[u] - es[i].cost && es[i].capacity > 0) {
                dis[v] = dis[u] - es[i].cost;
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
    vis[u]      = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] - es[i].cost) { continue; }
        int outFlowV = dfs(v, min(inFlow - outFlow, es[i].capacity), ans);
        if (outFlowV > 0) {
            outFlow += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            ans.second += outFlowV * es[i].cost;
            if (outFlow == inFlow) { break; }
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
    cin >> a >> b >> n >> m;
    s = ++idCnt, t = ++idCnt;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) { id[i][j] = ++idCnt; }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cost;
            addFlow(id[i][j], id[i][j + 1], 1, cost);
            addFlow(id[i][j], id[i][j + 1], INF, 0);
        }
    }
    for (int j = 0; j <= m; j++) {
        for (int i = 0; i < n; i++) {
            cin >> cost;
            addFlow(id[i][j], id[i + 1][j], 1, cost);
            addFlow(id[i][j], id[i + 1][j], INF, 0);
        }
    }
    int num = 0, x = 0, y = 0;
    for (int i = 0; i < a; i++) {
        cin >> num >> x >> y;
        addFlow(s, id[x][y], num, 0);
    }
    for (int i = 0; i < b; i++) {
        cin >> num >> x >> y;
        addFlow(id[x][y], t, num, 0);
    }
    cout << MCMFDinic().second << endl;
    return 0;
}
