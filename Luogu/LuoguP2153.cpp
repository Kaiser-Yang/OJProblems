// problem statement: https://www.luogu.com.cn/problem/P2153

#include <bits/stdc++.h>

constexpr int MAXN = 210;
constexpr int MAXM = 2e4 + 10;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, m, s, t, u, v, cost, ecnt;
int head[MAXN * 2], cur[MAXN * 2], dis[MAXN * 2];
bool vis[MAXN * 2];

struct Graph
{
    int to, nex, capacity, cost;
} es[MAXM * 2 + MAXN * 2];

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

int dfs(int u, int inFLow, pair<int, int> &ans)
{
    if (u == t || inFLow == 0) { return inFLow; }
    vis[u] = true;
    int outFLow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(inFLow - outFLow, es[i].capacity), ans);
        if (delta > 0) {
            outFLow += delta;
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            if (outFLow == inFLow) { break; }
        }
    }
    vis[u] = false;
    return outFLow;
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
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    s = 1, t = n;
    for (int i = 2; i < n;i ++) {
        addEdge(i, i + n, 1, 0);
        addEdge(i + n, i, 0, 0);
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> cost;
        if (u == s) {
            addEdge(u, v, 1, cost);
            addEdge(v, u, 0, -cost);
        } else {
            addEdge(u + n, v, 1, cost);
            addEdge(v, u + n, 0, -cost);
        }
    }
    auto &&ans = MCMFDinic();
    cout << ans.first << " " << ans.second << "\n";
	return 0;
}
