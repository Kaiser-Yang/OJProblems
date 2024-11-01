// problem statement: https://www.luogu.com.cn/problem/P3547
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 1e5 + 10;
constexpr int INF = 0x3f3f3f3f;

int n, m, k, a, b, u, v;
int ans[MAXN], dis[MAXN];
bool vis[MAXN];

struct Graph {
    int ecnt;
    int head[MAXN], to[MAXM << 1], nex[MAXM << 1], pre[MAXM << 1];

    Graph() {
        ecnt = 1;  // must count fron 1, otherwise pre[head[u]] may call pre[-1]
        memset(head, 0, sizeof(head));
    }

    void addEdge(int u, int v) {
        to[ecnt] = v;
        nex[ecnt] = head[u];
        pre[head[u]] = ecnt;
        head[u] = ecnt++;
    }

    void delEdge(int u, int i) {
        nex[pre[i]] = nex[i];
        pre[nex[i]] = pre[i];
        if (head[u] == i) { head[u] = nex[i]; }
    }
} g, newG;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k >> a >> b;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g.addEdge(u, v);
        g.addEdge(v, u);
        newG.addEdge(u, v);
        newG.addEdge(v, u);
    }
    memset(dis, 0x3f, sizeof(dis));
    queue<int> q;
    q.push(k);
    dis[k] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = g.head[u]; i != 0; i = g.nex[i]) {
            int v = g.to[i];
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dis[i] != INF) {
            ans[i] = min(dis[i] * a, dis[i] / 2 * b + dis[i] % 2 * a);
        } else {
            ans[i] = 1e9;
        }
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[k] = 0;
    q.push(k);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = g.head[u]; i != 0; i = g.nex[i]) {
            int v = g.to[i];
            vis[v] = true;
        }
        for (int i = g.head[u]; i != 0; i = g.nex[i]) {
            int v = g.to[i];
            for (int j = newG.head[v]; j != 0; j = newG.nex[j]) {
                int w = newG.to[j];
                if (vis[w] || dis[w] != INF) { continue; }
                dis[w] = dis[u] + 1;
                q.push(w);
                newG.delEdge(v, j);
            }
        }
        for (int i = g.head[u]; i != 0; i = g.nex[i]) {
            int v = g.to[i];
            vis[v] = false;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dis[i] != INF) { ans[i] = min(ans[i], b * dis[i]); }
        cout << ans[i] << endl;
    }
    return 0;
}