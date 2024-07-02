// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 1e5 + 10;
constexpr int INF  = 0x3f3f3f3f;

int n, m, q, u, v, node, l, ecnt;
int head[MAXN], dis[MAXN][2];

struct Edge {
    int to, nex;
} es[MAXM * 2];

void addEdge(int u, int v) {
    es[ecnt].to  = v;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

void bfs() {
    memset(dis, 0x3f, sizeof(dis));
    vector<vector<bool>> vis(n + 1, vector<bool>(2, false));
    queue<int> q;
    q.push(1);
    vis[1][0] = true;
    dis[1][0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (!vis[v][0] && dis[u][1] < INF) {
                vis[v][0] = true;
                dis[v][0] = dis[u][1] + 1;
                q.push(v);
            }
            if (!vis[v][1] && dis[u][0] < INF) {
                vis[v][1] = true;
                dis[v][1] = dis[u][0] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    bfs();
    for (int i = 0; i < q; i++) {
        cin >> node >> l;
        if (l % 2 == 0 && dis[node][0] <= l) {
            cout << "Yes" << endl;
        } else if (l % 2 == 1 && dis[node][1] <= l) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
