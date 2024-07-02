#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int n, u, v, fathest, node1, node2, diameter;
long long ans;
vector<int> g[MAXN], order;
int depth[MAXN], dis1[MAXN], dis2[MAXN], degree[MAXN], parent[MAXN];
bool onDiameter[MAXN];
set<int> leafNode;

void addEdge(int u, int v) { g[u].push_back(v); }

void fathestNode(int u, int par) {
    parent[u] = par;
    depth[u]  = depth[par] + 1;
    if (depth[u] > depth[fathest]) { fathest = u; }
    for (int v : g[u]) {
        if (v == par) { continue; }
        fathestNode(v, u);
    }
}

void getDis(int s, int *dis) {
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dis[v] != -1) { continue; }
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
}

void bfs() {
    memset(dis1, -1, sizeof(dis1));
    getDis(node1, dis1);
    memset(dis2, -1, sizeof(dis2));
    getDis(node2, dis2);
}

void toposort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            q.push(i);
            order.push_back(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (--degree[v] == 1) {
                order.push_back(v);
                q.push(v);
            }
        }
    }
}

void outputAnsDetail() {
    cout << ans << endl;
    for (int u : order) {
        if (onDiameter[u]) {
            continue;
        } else if (dis1[u] > dis2[u]) {
            cout << node1 << " " << u << " " << u << endl;
        } else {
            cout << node2 << " " << u << " " << u << endl;
        }
    }
    int now = node2;
    while (now != node1) {
        cout << node1 << " " << now << " " << now << endl;
        now = parent[now];
    };
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
        degree[u]++;
        degree[v]++;
    }
    fathestNode(1, 0);
    node1   = fathest;
    fathest = 0;
    fathestNode(node1, 0);
    node2    = fathest;
    diameter = depth[node2] - 1;
    int now  = node2;
    do { onDiameter[now] = true; } while ((now = parent[now]) != 0);
    bfs();  // get the dis1[i]: distance between node1 and i;
            // 		  dis2[i]; distance between node2 and i;
    toposort();
    for (int u : order) {
        if (onDiameter[u]) {
            continue;
        } else {
            ans += 1LL * max(dis1[u], dis2[u]);
        }
    }
    ans += 1LL * (diameter + 1) * diameter / 2;
    outputAnsDetail();
    return 0;
}
