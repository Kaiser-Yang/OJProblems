// problem statement: https://www.luogu.com.cn/problem/P1333

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 250000;

int n, scc;
bool vis[MAXN << 1];
int degree[MAXN << 1];

map<string, int> id;
string color[2];

vector<int> g[MAXN << 1];

void dfs(int u)
{
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) { continue; }
        dfs(v);
    }
}

int main()
{
    // freopen("test.in", "r" , stdin);
	ios::sync_with_stdio(false);
    while (cin >> color[0] >> color[1]) {
        if (id.count(color[0]) == 0) { id[color[0]] = n++; }
        if (id.count(color[1]) == 0) { id[color[1]] = n++; }
        int u = id[color[0]], v = id[color[1]];
        degree[u]++;
        degree[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (vis[i] || degree[i] == 0) {continue; }
        scc++;
        dfs(i);
    }
    if (scc > 1) {
        cout << "Impossible\n";
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) { if (degree[i] & 1) { cnt++; } }
    if (cnt != 0 && cnt != 2) {
        cout << "Impossible\n";
        return 0;
    }
    cout << "Possible" << endl;
	return 0;
}
