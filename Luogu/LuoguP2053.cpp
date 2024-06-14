// problem statement: https://www.luogu.com.cn/problem/P2053

#include <bits/stdc++.h>

constexpr int MAXN = 60 + 10;
constexpr int MAXM = 9 + 10;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, m, cost, s, t, ecnt;
int head[MAXN + MAXM * MAXN], cur[MAXN + MAXM * MAXN], dis[MAXN + MAXM * MAXN];
bool vis[MAXN + MAXM * MAXN];

struct Graph
{
    int to, nex, capacity, cost;
} es[2 * MAXM * MAXN * MAXN];

void addEdge(int u, int v, int capacity, int cost)
{
    es[ecnt] = {v, head[u], capacity, cost};
    head[u] = ecnt++;
}

bool spfa()
{
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
            if (dis[v] > dis[u] + es[i].cost && es[i].capacity > 0) {
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

int dfs(int u, int inFlow, pair<int, int> &ans)
{
    if (u == t || inFlow == 0) { return inFlow; }
    vis[u] = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
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

pair<int, int> MCMFDinic()
{
    pair<int, int> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        while ((flow = dfs(s, INF, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> m >> n;
    s = 0, t = n * m + n + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // technician j repairs car i with cost;
            cin >> cost;
            for (int k = 1; k <= n; k++) {
                addEdge(j * n + k, i, 1, k * cost);
                addEdge(i, j * n + k, 0, -k * cost);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        addEdge(i, t, 1, 0);
        addEdge(t, i, 0, 0);
    }
    for (int i = 1; i <= n * m; i++) {
        addEdge(s, i + n, 1, 0);
        addEdge(i + n, s, 0, 0);
    }
    cout << fixed << setprecision(2) << 1. * MCMFDinic().second / n << "\n";
	return 0;
}
