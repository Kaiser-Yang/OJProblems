// problem statement: https://codeforces.com/problemset/problem/2029/D

#include <bits/stdc++.h>

using namespace std;

int T, n, m, u, v;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vector<set<int>> g(n + 1);
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            g[u].insert(v);
            g[v].insert(u);
        }
        vector<tuple<int, int, int>> ans;
        for (int i = 1; i <= n; i++) {
            while (g[i].size() >= 2) {
                u = *g[i].begin();
                g[i].erase(u);
                v = *g[i].begin();
                g[i].erase(v);
                g[u].erase(i);
                g[v].erase(i);
                if (g[u].count(v) != 0) {
                    g[u].erase(v);
                    g[v].erase(u);
                } else {
                    g[u].insert(v);
                    g[v].insert(u);
                }
                ans.emplace_back(i, u, v);
            }
        }
        vector<pair<int, int>> two_nodes;
        vector<int> one_node;
        for (int i = 1; i <= n; i++) {
            if (g[i].size() == 0) {
                one_node.push_back(i);
            } else if (*g[i].begin() > i) {
                two_nodes.emplace_back(i, *g[i].begin());
            }
        }
        if (!two_nodes.empty()) {
            auto [u, v] = two_nodes.back();
            two_nodes.pop_back();
            for (int i : one_node) {
                ans.emplace_back(i, u, v);
                u = i;
            }
            for (auto [a, b] : two_nodes) { ans.emplace_back(a, b, u); }
        }
        cout << ans.size() << '\n';
        for (auto &&[a, b, c] : ans) { cout << a << ' ' << b << ' ' << c << '\n'; }
    }
    return 0;
}
