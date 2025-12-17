#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

const int INF = 0x3fffffff;
const int MAXN = 210;
const int MAXM = 5010;

struct Edge {
    int from, to, nex;
    long long flow, capacity;
} es[MAXM << 1];

int n, m, s, t;
int u, v, c;

int ecnt;
int head[MAXN], nowHead[MAXN];
int depth[MAXN];

void addEdge(int u, int v, int c, int f) {
    es[ecnt].from = u;
    es[ecnt].to = v;
    es[ecnt].capacity = c;
    es[ecnt].flow = f;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

long long EK() {
    long long maxFlow = 0;
    while (true) {
        vector<long long> x(n + 1, 0);
        vector<int> previousPathNumber(n + 1, -1);
        queue<int> q;
        q.push(s);
        x[s] = numeric_limits<long long>::max();
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = es[i].nex) {
                int v = es[i].to;
                if (previousPathNumber[v] == -1 && es[i].capacity > es[i].flow) {
                    previousPathNumber[v] = i;
                    x[v] = min(x[u], es[i].capacity - es[i].flow);
                    q.push(v);
                }
            }
            if (previousPathNumber[t] != -1) { break; }
        }
        if (x[t] == 0) { break; }
        maxFlow += x[t];
        for (int u = t; u != s; u = es[previousPathNumber[u]].from) {
            es[previousPathNumber[u]].flow += x[t];
            es[previousPathNumber[u] ^ 1].flow -= x[t];
        }
    }
    return maxFlow;
}

bool findAugmentedPath() {
    queue<int> q;
    memset(depth, 0, sizeof(depth));
    q.push(s);
    depth[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        nowHead[u] = head[u];
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (depth[v] == 0 && es[i].capacity > es[i].flow) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    return depth[t] != 0;
}

long long dfs(int u, long long inFlow) {
    if (u == t || inFlow == 0) { return inFlow; }
    long long outFlow = 0;
    for (int i = nowHead[u]; i != -1; i = es[i].nex) {
        nowHead[u] = es[i].nex;
        int v = es[i].to;
        if (depth[v] != depth[u] + 1 || es[i].capacity == es[i].flow) { continue; }
        long long x = dfs(v, min(es[i].capacity - es[i].flow, inFlow - outFlow));
        es[i].flow += x;
        es[i ^ 1].flow -= x;
        outFlow += x;
        if (outFlow == inFlow) { return outFlow; }
    }
    return outFlow;
}

long long Dinic() {
    long long maxFlow = 0;
    while (findAugmentedPath()) { maxFlow += dfs(s, INF); }
    return maxFlow;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;
        addEdge(u, v, c, 0);
        addEdge(v, u, 0, 0);
    }
    cout << Dinic() << endl;
    // cout << EK() << endl;
    return 0;
}