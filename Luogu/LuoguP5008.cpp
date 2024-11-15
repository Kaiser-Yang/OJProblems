// problem statement: https://www.luogu.com.cn/problem/P5008

#include <bits/stdc++.h>

using namespace std;

int n, m, k, u, v;
vector<long long> w;
vector<vector<int>> g;

int cnt, col;
vector<bool> in_stack;
vector<int> dfn, low, color, min_w_index;
vector<long long> min_w;
stack<int> s;

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    in_stack[u] = true;
    s.push(u);
    for (auto &&v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        col++;
        while (s.top() != u) {
            if (w[s.top()] < min_w[col]) {
                min_w[col] = w[s.top()];
                min_w_index[col] = s.top();
            }
            color[s.top()] = col;
            in_stack[s.top()] = false;
            s.pop();
        }
        if (w[u] < min_w[col]) {
            min_w[col] = w[u];
            min_w_index[col] = u;
        }
        color[s.top()] = col;
        in_stack[s.top()] = false;
        s.pop();
    }
}

void init() {
    g.resize(n + 1);
    w.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
    color.resize(n + 1);
    in_stack.resize(n + 1);
    min_w.resize(n + 1, std::numeric_limits<long long>::max());
    min_w_index.resize(n + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    init();
    for (int i = 1; i <= n; i++) { cin >> w[i]; }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) { tarjan(i); }
    }
    for (int i = 1; i <= col; i++) { w[min_w_index[i]] = 0; }
    for (int u = 1; u <= n; u++) {
        for (auto &&v : g[u]) {
            if (color[u] != color[v] || (u == v && u == min_w_index[color[u]])) {
                w[min_w_index[color[v]]] = min_w[color[v]];
            }
        }
    }
    long long ans = 0;
    sort(w.begin() + 1, w.end(), greater<long long>());
    for (int i = 1; i <= k; i++) { ans += w[i]; }
    cout << ans << '\n';
    return 0;
}
