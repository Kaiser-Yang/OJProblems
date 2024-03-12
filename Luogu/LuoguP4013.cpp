// problem statement: https://www.luogu.com.cn/problem/P4013

#include <bits/stdc++.h>

constexpr int MAXN = 20 + 4;
constexpr int MAXM = 20 + 4;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, m, idCnt;
int dx[] = {1, 1};
int dy[] = {0, 1};
map<pair<int, int>, int> id;
int num[MAXN][MAXM + MAXN];
int s, t, ecnt;
int head[(MAXN + MAXM) * MAXN * 2], cur[(MAXN + MAXM) * MAXN * 2], dis[(MAXN + MAXM) * MAXN * 2];
bool vis[(MAXN + MAXM) * MAXN * 2];

struct Graph
{
    int to, nex, capacity, cost;
} es[18 * (MAXN + MAXM) * MAXN];

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

int dfs(int u, int inFlow, pair<int, int> &ans)
{
    if (u == t || inFlow == 0) { return inFlow; }
    vis[u] = true;
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
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            id[{i, j}] = ++idCnt;
            cin >> num[i][j];
        }
    }
    s = 0, t = 2 * idCnt + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = id[{i, j}], v = u + idCnt;
            addEdge(u, v, 1, num[i][j]);
            addEdge(v, u, 0, -num[i][j]);
            if (i == 1) {
                addEdge(s, u, 1, 0);
                addEdge(u, s, 0, 0);
            }
            if (i == n) {
                addEdge(v, t, 1, 0);
                addEdge(t, v, 0, 0);
            }
            for (int k = 0; k < 2; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > n || ny < 1 || ny > m + nx - 1) { continue; }
                u = id[{i, j}] + idCnt, v = id[{nx, ny}];
                addEdge(u, v, 1, 0);
                addEdge(v, u, 0, 0);
            }
        }
    }
    cout << MCMFDinic().second << "\n";
    for (int i = 0; i < ecnt; i += 2) {
        es[i].capacity += es[i ^ 1].capacity;
        es[i ^ 1].capacity = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = id[{i, j}], v = u + idCnt;
            if (i == n) {
                addEdge(v, t, INF, 0);
                addEdge(t, v, 0, 0);
            }
            addEdge(u, v, INF, num[i][j]);
            addEdge(v, u, 0, -num[i][j]);
        }
    }
    cout << MCMFDinic().second << "\n";
    for (int i = 0; i < ecnt; i += 2) {
        es[i].capacity += es[i ^ 1].capacity;
        es[i ^ 1].capacity = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = id[{i, j}], v = u + idCnt;
            for (int k = 0; k < 2; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > n || ny < 1 || ny > m + nx - 1) { continue; }
                u = id[{i, j}] + idCnt, v = id[{nx, ny}];
                addEdge(u, v, INF, 0);
                addEdge(v, u, 0, 0);
            }
        }
    }
    cout << MCMFDinic().second << endl;
	return 0;
}
