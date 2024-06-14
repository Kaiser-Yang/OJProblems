// problem statement: https://loj.ac/p/191
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, u, v;
int degree[MAXN], cnt[MAXN];
long long ans;
bool vis[MAXN];

vector<int> g[MAXN], newG[MAXN];

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (degree[v] < degree[u] || 
                (degree[v] == degree[u] && v < u)) { newG[u].push_back(v); }
        }
    }
    for (int a = 1; a <= n; a++) {
        for (int b : newG[a]) {
            for (int c : g[b]) {
                if (degree[c] > degree[a] ||
                    (degree[c] == degree[a] && c >= a)) { continue; }
                ans += cnt[c]; 
                cnt[c]++;
            }
        }
        for (int b : newG[a]) {
            for (int c : g[b]) { cnt[c] = 0; }
        }
    }
    cout << ans << endl;
	return 0;
}
