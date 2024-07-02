// problem statement: https://www.luogu.com.cn/problem/P4009

#include <bits/stdc++.h>

constexpr int MAXN = 100 + 10;
constexpr int MAXK = 10 + 2;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, k, a, b, c;
int g[MAXN][MAXN];
int s, t, ecnt;
int head[MAXK * MAXN * MAXN], cur[MAXK * MAXN * MAXN], dis[MAXK * MAXN * MAXN];
bool vis[MAXK * MAXN * MAXN];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct Graph {
    int to, nex, capacity, cost;
} es[MAXN * MAXN * MAXK * 4 * 2];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

int getID(int i, int j, int level) { return (i - 1) * n + j + level * n * n + 1; }

bool spfa() {
    auto &inq = vis;
    memset(dis, 0x3f, sizeof(dis));
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
            if (es[i].capacity == 0) { continue; }
            if (dis[v] > dis[u] + es[i].cost) {
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
        if (es[i].capacity == 0 || vis[v] || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFlow), ans);
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            outFlow += delta;
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
    cin >> n >> k >> a >> b >> c;
    s = 0, t = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) { cin >> g[i][j]; }
    }
    addEdge(s, getID(1, 1, 0), 1, 0);
    addEdge(getID(1, 1, 0), s, 0, 0);
    for (int level = 0; level <= k; level++) {
        addEdge(getID(n, n, level), t, 1, 0);
        addEdge(t, getID(n, n, level), 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == 1) {
                for (int level = 1; level <= k; level++) {
                    addEdge(getID(i, j, level), getID(i, j, 0), 1, a);
                    addEdge(getID(i, j, 0), getID(i, j, level), 0, -a);
                }
                for (int kk = 0; kk < 4; kk++) {
                    int nx = i + dx[kk], ny = j + dy[kk];
                    if (nx < 1 || nx > n || ny < 1 || ny > n) { continue; }
                    if (nx < i || ny < j) {
                        addEdge(getID(i, j, 0), getID(nx, ny, 1), 1, b);
                        addEdge(getID(nx, ny, 1), getID(i, j, 0), 0, -b);
                    } else {
                        addEdge(getID(i, j, 0), getID(nx, ny, 1), 1, 0);
                        addEdge(getID(nx, ny, 1), getID(i, j, 0), 0, 0);
                    }
                }
            } else {
                for (int level = 0; level < k; level++) {
                    for (int kk = 0; kk < 4; kk++) {
                        int nx = i + dx[kk], ny = j + dy[kk];
                        if (nx < 1 || nx > n || ny < 1 || ny > n) { continue; }
                        if (nx < i || ny < j) {
                            addEdge(getID(i, j, level), getID(nx, ny, level + 1), 1, b);
                            addEdge(getID(nx, ny, level + 1), getID(i, j, level), 0, -b);
                        } else {
                            addEdge(getID(i, j, level), getID(nx, ny, level + 1), 1, 0);
                            addEdge(getID(nx, ny, level + 1), getID(i, j, level), 0, 0);
                        }
                    }
                }
                addEdge(getID(i, j, k), getID(i, j, 0), 1, a + c);
                addEdge(getID(i, j, 0), getID(i, j, k), 0, -(a + c));
            }
        }
    }
    cout << MCMFDinic().second << "\n";
    return 0;
}
