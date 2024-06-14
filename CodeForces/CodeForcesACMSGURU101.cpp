// problem statement: https://codeforces.com/problemsets/acmsguru/problem/99999/101

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;

int n, scc, oddNodeCnt, startNode = -1;
int u[MAXN], v[MAXN], degree[7], cnt[7];
bool vis[7];

stack<pair<int, int>> ans;

struct Edge
{
    int to, dominoNumber;
    bool deleted;
    int reverseEdge;
};

vector<Edge> g[7];

void dfs(int u)
{
    vis[u] = true;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        if (vis[v]) { continue; }
        dfs(v);
    }
}

void hierholzer(int u, int par, int dominoNumber)
{
    for (int &i = cnt[u]; i < g[u].size(); ) {
        if (g[u][i].deleted) {
            i++;
            continue;
        }
        int v = g[u][i].to, newDominoNumber = g[u][i].dominoNumber;
        g[u][i].deleted = g[v][g[u][i].reverseEdge].deleted = true;
        i++;
        hierholzer(v, u, newDominoNumber);
    }
    ans.push({par, dominoNumber});
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> u[i] >> v[i];
        degree[u[i]]++;
        degree[v[i]]++;
        if (u[i] == v[i]) {
            g[u[i]].push_back({v[i], i, false, (int)g[v[i]].size() + 1});
            g[v[i]].push_back({u[i], i, false, (int)g[u[i]].size() - 1});
            continue; 
        }
        g[u[i]].push_back({v[i], i, false, (int)g[v[i]].size()});
        g[v[i]].push_back({u[i], i, false, (int)g[u[i]].size() - 1});
    }
    for (int i = 0; i <= 6; i++) {
        if (degree[i] == 0 || vis[i]) { continue; }
        scc++;
        dfs(i);
    }
    if (scc > 1) {
        cout << "No solution\n";
        return 0;
    }
    for (int i = 0; i <= 6; i++) {
        if (degree[i] == 0 || degree[i] % 2 == 0) { continue; }
        oddNodeCnt++;
        startNode = i;
    }
    if (oddNodeCnt != 0 && oddNodeCnt != 2) {
        cout << "No solution\n";
        return 0;
    }
    if (startNode == -1) {
        for (int i = 0; i <= 6; i++) {
            if (degree[i] == 0) { continue; }
            startNode = i;
            break;
        }
        if (startNode == -1) { return 0; }
    }
    hierholzer(startNode, -1, -1);
    ans.pop();
    while (!ans.empty()) {
        auto item = ans.top();
        ans.pop();
        int u = item.first, index = item.second;
        if (u == ::u[index]) { cout << index << " +\n"; }
        else { cout << index << " -\n"; }
    }
	return 0;
}
