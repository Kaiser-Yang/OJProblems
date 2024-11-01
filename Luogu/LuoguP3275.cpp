// problem statement: https://www.luogu.com.cn/problem/P3275
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 1e5 + 10;

int n, m, op, u, v, ecnt, reverseEcnt, cnt, colorCnt;
int dis[MAXN], head[MAXN], reverseHead[MAXN], dfn[MAXN], low[MAXN], color[MAXN], inDegree[MAXN];
stack<int> s;
bool ins[MAXN];

struct Graph {
    int to, nex, w;
} es[MAXM << 1], reverseEs[MAXM << 1];

struct Edge {
    int u, v, w;
};

vector<Edge> edge;

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

void addEdgeReverse(int u, int v, int w) {
    reverseEs[reverseEcnt].to = v;
    reverseEs[reverseEcnt].w = w;
    reverseEs[reverseEcnt].nex = reverseHead[u];
    reverseHead[u] = reverseEcnt++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    s.push(u);
    ins[u] = true;
    for (int i = reverseHead[u]; i != -1; i = reverseEs[i].nex) {
        int v = reverseEs[i].to;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        colorCnt++;
        while (s.top() != u) {
            color[s.top()] = colorCnt;
            ins[s.top()] = false;
            s.pop();
        }
        color[s.top()] = colorCnt;
        ins[s.top()] = false;
        s.pop();
    }
}

bool toposort() {
    memset(dis, 0x00, sizeof(dis));
    queue<int> q;
    for (int i = 1; i <= colorCnt; i++) {
        if (inDegree[i] != 0) { continue; }
        q.push(i);
        dis[i] = 1;
    }
    int res = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res++;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to, w = es[i].w;
            dis[v] = max(dis[v], dis[u] + w);
            if ((--inDegree[v]) == 0) { q.push(v); }
        }
    }
    return res == colorCnt;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    memset(reverseHead, 0xff, sizeof(reverseHead));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> op >> u >> v;
        if (op == 1) {
            addEdgeReverse(v, u, 0);
            addEdgeReverse(u, v, 0);
        } else if (op == 2) {
            edge.push_back({u, v, 1});
        } else if (op == 3) {
            addEdgeReverse(v, u, 0);
        } else if (op == 4) {
            edge.push_back({v, u, 1});
        } else {
            addEdgeReverse(u, v, 0);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] != 0) { continue; }
        tarjan(i);
    }
    for (int u = 1; u <= n; u++) {
        for (int i = reverseHead[u]; i != -1; i = reverseEs[i].nex) {
            int v = reverseEs[i].to, w = reverseEs[i].w;
            if (color[u] == color[v]) { continue; }
            addEdge(color[u], color[v], w);
            inDegree[color[v]]++;
        }
    }
    for (auto item : edge) {
        addEdge(color[item.u], color[item.v], item.w);
        inDegree[color[item.v]]++;
    }
    if (!toposort()) {
        cout << "-1\n";
        return 0;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) { ans += dis[color[i]]; }
    cout << ans << endl;
    return 0;
}
