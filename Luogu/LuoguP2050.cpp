// problem statement: https://www.luogu.com.cn/problem/P2050

#include <bits/stdc++.h>

constexpr int MAXN = 40 + 5;
constexpr int MAXM = 100 + 5;
constexpr int MAX_TOT_P = 800 + 10;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n, m, ecnt, totP, s, t;
int p[MAXN];
int head[MAX_TOT_P * MAXM + MAXN], cur[MAX_TOT_P * MAXM + MAXN];
int dis[MAX_TOT_P * MAXM + MAXN], parent[MAX_TOT_P * MAXM + MAXN];
int cost[MAXM][MAXN], level[MAXM];
bool vis[MAX_TOT_P * MAXM + MAXN];

struct Graph
{
    int to, nex, capacity, cost;
} es[2 * MAX_TOT_P * MAXN * MAXM];

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

int dfs(int u, int inFlow, pair<int, int> &ans)
{
    if (u == t || inFlow == 0) { return inFlow; }
    int outFlow = 0;
    vis[u] = true;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(inFlow - outFlow, es[i].capacity), ans);
        if (delta > 0) {
            outFlow += delta;
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            parent[v] = u;
            if (inFlow == outFlow) { break; }
        }
    }
    vis[u] = false;
    return outFlow;
}

int chefID(int i, int j) { return n + (i - 1) * totP + j; }

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        totP += p[i];
    }
    s = 0, t = n + (m - 1) * totP + totP + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // chef j cooks food i with cost
            cin >> cost[j][i];
            addEdge(chefID(j, 1), i, 1, cost[j][i]);
            addEdge(i, chefID(j, 1), 0, -cost[j][i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        addEdge(i, t, p[i], 0);
        addEdge(t, i, 0, 0);
    }
    for (int i = 1; i <= m; i++) {
        level[i] = 1;
        addEdge(s, chefID(i, 1), 1, 0);
        addEdge(chefID(i, 1), s, 0, 0);
    }
    pair<int, int> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        memset(parent, 0xff, sizeof(parent));
        while ((flow = dfs(s, INF, ans)) != 0) { ans.first += flow; }
        for (int j = 1; j <= m; j++) {
            if (parent[chefID(j, level[j])] != -1 && level[j] < totP) {
                level[j]++;
                for (int i = 1; i <= n; i++) {
                    addEdge(chefID(j, level[j]), i, 1, level[j] * cost[j][i]);
                    addEdge(i, chefID(j, level[j]), 0, -level[j] * cost[j][i]);
                }
                addEdge(s, chefID(j, level[j]), 1, 0);
                addEdge(chefID(j, level[j]), s, 0, 0);
            }
        }
    }
    cout << ans.second << "\n";
	return 0;
}
