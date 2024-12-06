// problem statement: https://codeforces.com/contest/2050/problem/G

#include <bits/stdc++.h>

using namespace std;

int T, n, ans;
vector<int> degree;
vector<vector<int>> g;

int dfs(int u, int par) {
    int max_val = 0, sub_max_val = 0;
    for (int v : g[u]) {
        if (v == par) { continue; }
        int tmp = dfs(v, u);
        if (tmp > max_val) {
            sub_max_val = max_val;
            max_val = tmp;
        } else if (tmp > sub_max_val) {
            sub_max_val = tmp;
        }
    }
    ans = max(ans, degree[u]);
    ans = max(ans, max_val + sub_max_val + degree[u] - 2);
    ans = max(ans, max_val + degree[u] - 1);
    return max(degree[u] - 1, max_val + degree[u] - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        g.clear();
        g.resize(n + 1);
        degree.clear();
        degree.resize(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        ans = numeric_limits<int>::min();
        dfs(1, 0);
        cout << ans << '\n';
    }
    return 0;
}
