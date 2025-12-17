#include <bits/stdc++.h>

using namespace std;

int dfs(int u, vector<vector<int>> &g, int T) {
    if (g[u].empty()) { return 1; }
    vector<int> d;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        d.push_back(dfs(v, g, T));
    }
    sort(d.begin(), d.end());
    int c = (g[u].size() * T - 1) / 100 + 1;
    int ans = 0;
    for (int i = 0; i < c; i++) { ans += d[i]; }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int N, T;
    vector<int> fa;
    vector<vector<int>> g;
    while (cin >> N >> T && N != 0 && T != 0) {
        fa.resize(N + 1);
        for (int i = 1; i <= N; i++) { cin >> fa[i]; }
        g.clear();
        g.resize(N + 1);
        for (int i = 1; i <= N; i++) { g[fa[i]].push_back(i); }
        cout << dfs(0, g, T) << endl;
    }
    return 0;
}
