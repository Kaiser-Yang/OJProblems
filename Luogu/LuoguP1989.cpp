// problem statement: https://www.luogu.com.cn/problem/P1989

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, ans;
int u[MAXM], v[MAXM], degree[MAXN];
bool vis[MAXN];

vector<int> g[MAXN];

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
        degree[u[i]]++;
        degree[v[i]]++;
    }
    for (int i = 0; i < m; i++) {
        if (degree[u[i]] > degree[v[i]] || 
            (degree[u[i]] == degree[v[i]] && u[i] > v[i])) { swap(u[i], v[i]); }
        g[u[i]].push_back(v[i]);
    }
    for (int a = 1; a <= n; a++) {
        for (int b : g[a]) { vis[b] = true;} 
        for (int b : g[a]) {
            for (int c : g[b]) {
                ans += vis[c];
            }
        }
        for (int b : g[a]) { vis[b] = false; }
    }
    cout << ans << endl;
	return 0;
}
