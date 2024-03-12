// problem statement: https://www.luogu.com.cn/problem/P2774

#include <bits/stdc++.h>

constexpr int MAXN = 100 + 10;
constexpr int MAXM = 100 + 10;
constexpr int  INF = 0x3f3f3f3f;

using namespace std;

int n, m, ans;
int num[MAXN][MAXM];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int s, t, ecnt;
int head[MAXN * MAXM], cur[MAXN * MAXM], depth[MAXN * MAXM];

struct Graph
{
    int to, nex, capacity;
} es[10 * MAXN * MAXM];

void addEdge(int u, int v, int capacity)
{
    es[ecnt] = {v, head[u], capacity};
    head[u] = ecnt++;
}

int getID(int i, int j) { return (i - 1) * m + j; }

bool bfs()
{
    memset(depth, 0xff, sizeof(depth));
    queue<int> q;
    depth[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity == 0 || depth[v] != -1) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != -1;
}

int dfs(int u, int inFlow)
{
    if (u == t || inFlow == 0) { return inFlow; }
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (es[i].capacity == 0 || depth[v] != depth[u] + 1) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFlow));
        if (delta > 0) {
            outFlow += delta;
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            if (outFlow == inFlow) { break; }
        }
    }
    return outFlow;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> num[i][j];
            ans += num[i][j];
        }
    }
    s = 0, t = getID(n, m) + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int u = getID(i, j);
            if ((i + j) % 2 == 0) {
                addEdge(s, u, num[i][j]);
                addEdge(u, s, 0);
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx < 1 || nx > n || ny < 1 || ny > m) { continue; }
                    int v = getID(nx, ny);
                    addEdge(u, v, INF);
                    addEdge(v, u, 0);
                }
            } else {
                addEdge(u, t, num[i][j]);
                addEdge(t, u, 0);
            }
        }
    }
    cout << ans - dinic() << "\n";
	return 0;
}
