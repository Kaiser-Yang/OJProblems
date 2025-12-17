#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;

int n, c1, c2, u, v;
vector<int> g[MAXN];
vector<int> d[4];

template <typename T>
T myMin(T arg) {
    return arg;
}

template <typename T0, typename... T1>
T0 myMin(T0 arg0, T1... arg) {
    return min(arg0, myMin(arg...));
}

void addEdge(int u, int v) { g[u].push_back(v); }

void dp(int u, int fa) {
    d[0][u] = d[3][u] = 0;
    d[1][u] = c1;
    d[2][u] = c2;
    int res = 0, mi = numeric_limits<int>::max() / 10;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) { continue; }
        dp(v, u);
        int x = myMin(d[0][v], d[1][v], d[2][v]);
        d[0][u] += myMin(d[1][v], d[2][v]);
        d[1][u] += x;
        d[2][u] += myMin(d[0][v], d[1][v], d[2][v], d[3][v]);
        d[3][u] += x;
        res += x;
        mi = min(mi, d[2][v] - x);
    }
    res += mi;
    d[1][u] = min(d[1][u], res);
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> c1 >> c2 && !(n == 0 && c1 == 0 && c2 == 0)) {
        for (int i = 1; i <= n; i++) { g[i].clear(); }
        for (int i = 0; i < n - 1; i++) {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        for (int i = 0; i < 4; i++) {
            d[i].clear();
            d[i].resize(n + 1);
        }
        dp(1, 0);
        cout << myMin(d[0][1], d[1][1], d[2][1]) << endl;
    }
    return 0;
}
