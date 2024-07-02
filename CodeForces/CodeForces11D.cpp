// problem statement: https://codeforces.com/problemset/problem/11/D
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 20;

int n, m, u, v;
long long ans;
long long dp[1 << MAXN][MAXN];

vector<int> g[MAXN];

constexpr int lowbit(int x) { return x & (-x); }

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; i++) { dp[1 << i][i] = 1; }
    for (int s = 1; s < (1 << n); s++) {
        for (int u = 0; u < n; u++) {
            if (dp[s][u] == 0) { continue; }
            for (int v : g[u]) {
                if (lowbit(s) > (1 << v)) { continue; }
                if (s & (1 << v)) {
                    if (lowbit(s) == (1 << v)) { ans += dp[s][u]; }
                } else {
                    dp[s | (1 << v)][v] += dp[s][u];
                }
            }
        }
    }
    cout << (ans - m) / 2 << endl;
    return 0;
}
