// problem statement: https://www.luogu.com.cn/problem/P2754

#include <bits/stdc++.h>

constexpr int MAXN = 13 + 2;
constexpr int MAXM = 20 + 2;
constexpr int MAXK = 50 + 5;
constexpr int MAXR = MAXN + 2;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n, m, k;
int s, t, ecnt;
int head[(MAXN + MAXR * MAXK * MAXN) << 1], cur[(MAXN + MAXR * MAXK * MAXN) << 1];
int depth[(MAXN + MAXR * MAXK * MAXN) << 1], h[MAXN];

struct Graph {
    int to, nex, capacity;
} es[MAXR * MAXK * 2 * (MAXM + MAXN)];

void addEdge(int u, int v, int capacity) {
    es[ecnt].to = v;
    es[ecnt].capacity = capacity;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

bool bfs() {
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (depth[v] != 0 || es[i].capacity == 0) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != 0;
}

int dfs(int u, int flow) {
    if (u == t || flow == 0) { return flow; }
    int res = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (depth[v] != depth[u] + 1) { continue; }
        int outFlowV = dfs(v, min(flow - res, es[i].capacity));
        if (outFlowV > 0) {
            res += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            if (res == flow) { return res; }
        }
    }
    return res;
}

struct SpaceShip {
    int capacity;
    vector<int> station;
    int position(int time) { return station[time % station.size()]; }
} spaceShip[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

bool check() {
    for (int i = 0; i <= n + 2; i++) { h[i] = i; }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < spaceShip[i].station.size(); j++) {
            join(spaceShip[i].station[j - 1], spaceShip[i].station[j]);
        }
    }
    return same(0, t);
}

int getID(int i, int time) {
    if (i == t) { return t; }
    return i + time * (n + 2) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> k;
    s = 0, t = n + 2;
    int h = 0, r = 0, station = 0;
    for (int i = 1; i <= m; i++) {
        cin >> h >> r;
        spaceShip[i].capacity = h;
        for (int j = 0; j < r; j++) {
            cin >> station;
            if (station == -1) { station = t; }
            spaceShip[i].station.push_back(station);
        }
    }
    if (!check()) {
        cout << "0\n";
        return 0;
    }
    int res = 0;
    addEdge(s, getID(0, 0), INF);
    addEdge(getID(0, 0), s, 0);
    for (int ans = 1;; ans++) {
        for (int i = 0; i <= n; i++) {
            addEdge(getID(i, ans - 1), getID(i, ans), INF);
            addEdge(getID(i, ans), getID(i, ans - 1), 0);
        }
        for (int i = 1; i <= m; i++) {
            int u = getID(spaceShip[i].position(ans - 1), ans - 1);
            int v = getID(spaceShip[i].position(ans), ans);
            addEdge(u, v, spaceShip[i].capacity);
            addEdge(v, u, 0);
        }
        while (bfs()) {
            memcpy(cur, head, sizeof(head));
            res += dfs(s, INF);
        }
        if (res < k) { continue; }
        cout << ans << "\n";
        break;
    }
    return 0;
}
