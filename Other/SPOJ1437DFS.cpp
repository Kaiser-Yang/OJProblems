#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;

int n, u, v;

vector<int> g[MAXN];

pair<int, int> dfs(int u, int par) {
    pair<int, int> res{u, 0};
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == par) { continue; }
        auto temp = dfs(v, u);
        if (temp.second + 1 > res.second) {
            res.second = temp.second + 1;
            res.first = temp.first;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto res = dfs(1, 0);
    cout << dfs(res.first, 0).second << endl;
    return 0;
}
