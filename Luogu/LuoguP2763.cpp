// problem statement: https://www.luogu.com.cn/problem/P2763

#include <bits/stdc++.h>

constexpr int MAXN = 1e3 + 10;
constexpr int MAXK = 20 + 5;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int k, n;
int s, t, ecnt;
int head[MAXN + MAXK], cur[MAXN + MAXK], depth[MAXN + MAXK];
vector<int> ans[MAXK];

struct Graph {
    int to, nex, capacity;
} es[2 * MAXN * MAXK];

void addEdge(int u, int v, int capacity) {
    es[ecnt].to       = v;
    es[ecnt].capacity = capacity;
    es[ecnt].nex      = head[u];
    head[u]           = ecnt++;
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

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> k >> n;
    s = 0, t = k + n + 1;
    int num = 0, tot = 0;
    for (int i = 1; i <= k; i++) {
        cin >> num;
        tot += num;
        addEdge(i + n, t, num);
        addEdge(t, i + n, 0);
    }
    int p, temp;
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, 1);
        addEdge(i, s, 0);
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            addEdge(i, temp + n, 1);
            addEdge(temp + n, i, 0);
        }
    }
    if (dinic() == tot) {
        for (int u = 1; u <= n; u++) {
            for (int i = head[u]; i != -1; i = es[i].nex) {
                int v = es[i].to;
                if (v == s || v == t || es[i].capacity > 0) { continue; }
                ans[v - n].push_back(u);
            }
        }
        for (int i = 1; i <= k; i++) {
            cout << i << ": ";
            for (int id : ans[i]) { cout << id << " "; }
            cout << "\n";
        }
    } else {
        cout << "No Solution!\n";
    }
    return 0;
}
