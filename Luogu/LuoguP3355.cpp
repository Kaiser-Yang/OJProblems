// problem statement: https://www.luogu.com.cn/problem/P3355

#include <bits/stdc++.h>

constexpr int MAXN = 210;
constexpr int MAXM = MAXN * MAXN;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m;
int s, t, ecnt;
int head[MAXN * MAXN], cur[MAXN * MAXN], depth[MAXN * MAXN];
bool blocked[MAXN][MAXN];
int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

struct Graph {
    int to, nex, capacity;
} es[18 * MAXN * MAXN];

void addEdge(int u, int v, int capacity) {
    es[ecnt] = {v, head[u], capacity};
    head[u]  = ecnt++;
}

int getID(int i, int j) { return (i - 1) * n + j; }

bool bfs() {
    memset(depth, 0xff, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 0;
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

int dfs(int u, int inFlow) {
    if (u == t || inFlow == 0) { return inFlow; }
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (es[i].capacity == 0 || depth[v] != depth[u] + 1) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFlow));
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            outFlow += delta;
            if (inFlow == outFlow) { break; }
        }
    }
    return outFlow;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    int x = 0, y = 0;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        blocked[x][y] = true;
    }
    s = 0, t = getID(n, n) + 1;
    int ans = n * n - m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (blocked[i][j]) { continue; }
            if ((i + j) % 2 == 0) {
                addEdge(s, getID(i, j), 1);
                addEdge(getID(i, j), s, 0);
                for (int k = 0; k < 8; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx < 1 || nx > n || ny < 1 || ny > n || blocked[nx][ny]) { continue; }
                    addEdge(getID(i, j), getID(nx, ny), INF);
                    addEdge(getID(nx, ny), getID(i, j), 0);
                }
            } else {
                addEdge(getID(i, j), t, 1);
                addEdge(t, getID(i, j), 0);
            }
        }
    }
    cout << ans - dinic() << "\n";
    return 0;
}
