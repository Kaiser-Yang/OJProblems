// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int n, u, v, ecnt, node1, node2, fathest, ans;
int head[MAXN], parent[MAXN];
long long w, diameter;
long long pathLen[MAXN], dis1[MAXN], dis2[MAXN], dis[MAXN];
bool onDiameter[MAXN];

struct Edge {
    int to, nex;
    long long w;
} es[MAXN << 1];

void fathestNode(int u, int par) {
    parent[u] = par;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (v == par) { continue; }
        pathLen[v] = pathLen[u] + es[i].w;
        if (pathLen[v] > pathLen[fathest]) { fathest = v; }
        fathestNode(v, u);
    }
}

void addEdge(int u, int v, long long w) {
    es[ecnt].to  = v;
    es[ecnt].w   = w;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

void bfs(int s, long long *dis) {
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    long long res = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (onDiameter[v]) { continue; }
            if (dis[v] == -1) {
                dis[v] = dis[u] + es[i].w;
                if (onDiameter[s]) { res = max(res, dis[v]); }
                q.push(v);
            }
        }
    }
    if (onDiameter[s]) { dis[s] = res; }
}

void bfs() {
    memset(dis1, -1, sizeof(dis1));
    bfs(node1, dis1);
    memset(dis2, -1, sizeof(dis2));
    bfs(node2, dis2);
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    fathest          = 1;
    pathLen[fathest] = 0;
    fathestNode(1, 0);
    node1            = fathest;
    pathLen[fathest] = 0;
    fathestNode(node1, 0);
    node2    = fathest;
    diameter = pathLen[node2];
    bfs();
    int now = node2;
    do { onDiameter[now] = true; } while ((now = parent[now]) != 0);
    memset(dis, -1, sizeof(dis));
    for (int i = 1; i <= n; i++) {
        if (!onDiameter[i]) { continue; }
        bfs(i, dis);
    }
    now = node2;
    stack<int> s;
    while (now != 0) {
        s.push(now);
        if (dis1[now] == dis[now]) { break; }
        now = parent[now];
    }
    ans = s.size() - 1;
    while (!s.empty()) {
        now = s.top();
        s.pop();
        if (dis2[now] == dis[now]) { break; }
    }
    ans -= s.size();
    cout << diameter << endl << ans << endl;
    return 0;
}
