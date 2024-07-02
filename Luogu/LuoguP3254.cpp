// problem statement: https://www.luogu.com.cn/problem/P3254

#include <bits/stdc++.h>

constexpr int MAXN = 270 + 10;
constexpr int MAXM = 150 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m, r, c;
int ecnt, s, t;
int head[MAXN + MAXM], depth[MAXN + MAXM], cur[MAXN + MAXM];

struct Graph {
    int to, nex, capacity;
} es[2 * MAXN * MAXM];

void addEdge(int u, int v, int capacity) {
    es[ecnt] = {v, head[u], capacity};
    head[u]  = ecnt++;
}

bool bfs() {
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity == 0 || depth[v] != 0) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != 0;
}

int dfs(int u, int inFlow) {
    if (u == t || inFlow == 0) { return inFlow; }
    int outFLow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (es[i].capacity == 0 || depth[v] != depth[u] + 1) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFLow));
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            outFLow += delta;
            if (inFlow == outFLow) { break; }
        }
    }
    return outFLow;
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
    cin >> m >> n;
    s = 0, t = n + m + 1;
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        cin >> r;
        tot += r;
        addEdge(s, i, r);
        addEdge(i, s, 0);
    }
    for (int i = 1; i <= n; i++) {
        cin >> c;
        addEdge(m + i, t, c);
        addEdge(t, m + i, 0);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            addEdge(i, j + m, 1);
            addEdge(j + m, i, 0);
        }
    }
    if (dinic() == tot) {
        cout << "1\n";
        for (int u = 1; u <= m; u++) {
            for (int i = head[u]; i != -1; i = es[i].nex) {
                int v = es[i].to;
                if (v == s || v == t || es[i].capacity > 0) { continue; }
                cout << v - m << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "0\n";
    }
    return 0;
}
