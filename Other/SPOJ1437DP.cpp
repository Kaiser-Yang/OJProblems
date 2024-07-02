#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;

int n, u, v, ans;

vector<int> g[MAXN];

pair<int, int> dfs(int u, int par) {
    int maxPath = 0, subMaxPath = 0;
    for (int v : g[u]) {
        if (v == par) { continue; }
        auto temp = dfs(v, u);
        if (temp.first + 1 > maxPath) {
            subMaxPath = maxPath;
            maxPath    = temp.first + 1;
        } else if (temp.first + 1 > subMaxPath) {
            subMaxPath = temp.first + 1;
        }
    }
    ans = max(ans, maxPath + subMaxPath);
    return {maxPath, subMaxPath};
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(u, 0);
    cout << ans << endl;
    return 0;
}
