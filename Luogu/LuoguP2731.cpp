// problem statement: https://www.luogu.com.cn/problem/P2731
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 510;
constexpr int MAXM = 1030;

int n, m, u, v;
int degree[MAXN], reverseEdgeCnt[MAXN], cnt[MAXN];

stack<int> ans;

struct Edge
{
    int to;
    bool deleted;
    int reverseEdge;
    bool operator<(const Edge &other) { return to < other.to; }
};

vector<Edge> g[MAXN];

int getStartNode()
{
    for (int i = 1; i <= n; i++) {
        if (degree[i] & 1) { return i; }
    }
    for (int i = 1; i <= n; i++) {
        if (degree[i] > 0) { return i; }
    }
    return -1;
}

void hierholzer(int u)
{
    for (int &i = cnt[u]; i < g[u].size(); ) {
        int v = g[u][i].to;
        if (g[u][i].deleted) {
            i++;
            continue;
        }
        g[u][i].deleted = g[v][g[u][i].reverseEdge].deleted = true;
        i++;
        hierholzer(v);
    }
    // we cannot output u as soon as we enter hierholzer(),
    // because if there are a circle in the graph, the order will be wrong.
    ans.push(u);
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        n = max({n, u, v});
        g[u].push_back({v, false, 0});
        g[v].push_back({u, false, 0});
        degree[u]++;
        degree[v]++;
    }
    for (int i = 1; i <= n; i++) { sort(g[i].begin(), g[i].end()); }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            int v = g[i][j].to;
            g[i][j].reverseEdge = reverseEdgeCnt[v]++;
        }
    }
    int start = getStartNode();
    hierholzer(start);
    while (!ans.empty()) {
        cout << ans.top() << endl;
        ans.pop();
    }
	return 0;
}
