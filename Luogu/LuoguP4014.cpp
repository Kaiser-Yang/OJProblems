// problem statement: https://www.luogu.com.cn/problem/P4014

#include <bits/stdc++.h>

constexpr int MAXN = 50 + 5;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, s, t, ecnt, c;
int head[MAXN + MAXN], cur[MAXN + MAXN], dis[MAXN + MAXN];
bool vis[MAXN + MAXN];

struct Graph
{
    int to, nex, capacity, cost;
} es[2 * MAXN * MAXN];

void addEdge(int u, int v, int capacity, int cost)
{
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    dis[s] = 0;
    inq[s] = true;
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
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int u, int inFLow, pair<int, int> &ans)
{
    if (u == t || inFLow == 0) { return inFLow; }
    vis[u] = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFLow - outFlow), ans);
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            outFlow += delta;
            if (inFLow == outFlow) { break; }
        }
    }
    vis[u] = false;
    return outFlow;
}

pair<int, int> MCMFDinic()
{
    pair<int, int> ans;
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
    cin >> n;
    s = 0, t = n + n + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c;
            addEdge(i, j + n, 1, c);
            addEdge(j + n, i, 0, -c);
        }
        addEdge(s, i, 1, 0);
        addEdge(i, s, 0, 0);
        addEdge(i + n, t, 1, 0);
        addEdge(t, i + n, 0, 0);
    }
    cout << MCMFDinic().second << "\n";
    for (int i = 0; i < ecnt; i += 2) {
        es[i].capacity = 1;
        es[i ^ 1].capacity = 0;
        swap(es[i].cost, es[i ^ 1].cost);
    }
    cout << -MCMFDinic().second << "\n";
	return 0;
}
