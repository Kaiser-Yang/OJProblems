// problem statement: https://www.luogu.com.cn/problem/P2765

#include <bits/stdc++.h>

constexpr int MAXANS = 2010;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n;
int ans;
int s, t, ecnt;
int head[2 * MAXANS], cur[2 * MAXANS], depth[2 * MAXANS], h[MAXANS];
bool vis[2 * MAXANS];
vector<int> path, g[MAXANS];

struct Graph {
    int to, nex, capacity;
} es[MAXANS * MAXANS * 2];

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].capacity = w;
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

int dinic() {
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

void dfs(int u) {
    for (int i = head[u]; i != -1; i = es[i].nex) {
        if (i % 2 == 1 || es[i].capacity > 0 || es[i].to == t) { continue; }
        int v = es[i].to;
        if (v > MAXANS) { v -= MAXANS; }
        if (u != s) { join(u, v); }
        dfs(v);
    }
}

int findPath(int u) {
    path.push_back(u);
    for (const int &v : g[u]) {
        if (find(v) != find(u)) { continue; }
        return findPath(v) + 1;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n;
    s = 0, t = 2 * MAXANS - 1;
    while (true) {
        ans++;
        for (int i = 1; i < ans; i++) {
            int temp = sqrt(i + ans);
            if (temp * temp == i + ans) {
                addEdge(i, ans + MAXANS, 1);
                addEdge(ans + MAXANS, i, 0);
            }
        }
        addEdge(s, ans, 1);
        addEdge(ans, s, 0);
        addEdge(ans + MAXANS, t, 1);
        addEdge(t, ans + MAXANS, 0);
        static int res = 0;
        res += dinic();
        if (ans - res > n) {
            ans--;
            break;
        }
    }
    cout << ans << "\n";
    ecnt = 0;
    memset(head, 0xff, sizeof(head));
    for (int i = 1; i <= ans; i++) {
        for (int j = i + 1; j <= ans; j++) {
            int temp = sqrt(i + j);
            if (temp * temp == i + j) {
                g[i].push_back(j);
                addEdge(i, j + MAXANS, 1);
                addEdge(j + MAXANS, i, 0);
            }
        }
        addEdge(s, i, 1);
        addEdge(i, s, 0);
        addEdge(i + MAXANS, t, 1);
        addEdge(t, i + MAXANS, 0);
    }
    dinic();
    for (int i = 1; i <= ans; i++) { h[i] = i; }
    dfs(s);
    for (int i = 1; i <= ans; i++) {
        if (find(i) == i) {
            int cnt = 0;
            for (int j = 1; j <= ans; j++) { cnt += same(i, j); }
            for (int j = 1; j <= ans; j++) {
                path.clear();
                if (!same(i, j) || findPath(j) != cnt) { continue; }
                for (const int &id : path) { cout << id << " "; }
                cout << "\n";
                break;
            }
        }
    }
    return 0;
}
