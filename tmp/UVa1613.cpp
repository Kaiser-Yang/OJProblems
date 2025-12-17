#include <bits/stdc++.h>

using namespace std;

void dfs(int u, vector<vector<int>> &g, vector<int> &color, int k)
{
    for (int col = 1; col <= k; col++) {
        bool ok = true;
        for (int i = 0; i < g[u].size(); i++) {
            if (color[g[u][i]] == col) {
                ok = false;
                break;
            }
        }
        if (ok) {
            color[u] = col;
            break;
        }
    }
    if (color[u] == 0) { return; }
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (color[v] != 0) { continue; }
        dfs(v, g, color, k);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m, u, v;
    vector<vector<int>> g;
    vector<int> degree, color;
    while (cin >> n >> m) {
        g.clear();
        g.resize(n + 1);
        degree.clear();
        degree.resize(n + 1);
        color.clear();
        color.resize(n + 1);
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        int k = 0;
        for (int i = 1; i <= n; i++) {
            k = max(k, degree[i]);
        }
        if (k % 2 == 0) { k++; }
        dfs(1, g, color, k);
        cout << k << endl;
        for (int i = 1; i <= n; i++) { cout << color[i] << endl;}
        cout << endl;
    }
    return 0;
}
