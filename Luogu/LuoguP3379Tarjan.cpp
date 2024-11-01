// problem statement:

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 10;
const int MAXM = 5e5 + 10;

int n, m, s, ecnt, u, v;
int queryHead[MAXN], parent[MAXN];
bool visit[MAXN];

vector<int> g[MAXN];  // tree

struct QueryEdge {
    int from, to, nex, lca;
} queryEdge[MAXM << 1];

void addQueryEdge(int u, int v) {
    queryEdge[ecnt].to = v;
    queryEdge[ecnt].from = u;
    queryEdge[ecnt].nex = queryHead[u];
    queryHead[u] = ecnt++;
}

int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

void tarjan(int u) {
    visit[u] = true;
    parent[u] = u;
    for (int v : g[u]) {
        if (visit[v]) { continue; }
        tarjan(v);
        parent[v] = u;
    }
    for (int i = queryHead[u]; i != -1; i = queryEdge[i].nex) {
        int v = queryEdge[i].to;
        if (visit[v]) { queryEdge[i].lca = queryEdge[i ^ 1].lca = find(v); }
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(queryHead, 0xff, sizeof(queryHead));
    cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        addQueryEdge(u, v);
        addQueryEdge(v, u);
    }
    tarjan(s);
    for (int i = 0; i < m; i++) { cout << queryEdge[i * 2].lca << endl; }
    return 0;
}
