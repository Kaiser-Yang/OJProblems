// problem statement: https://codeforces.com/contest/985/problem/G
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, u[MAXM], v[MAXM], degree[MAXN];
bool vis[MAXN];
unsigned long long a, b, c, ans;
unsigned long long sum[MAXN];

vector<int> minG[MAXN], maxG[MAXN];

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> a >> b >> c;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
        if (u[i] > v[i]) { swap(u[i], v[i]); }
        degree[u[i]]++;
        degree[v[i]]++;
        minG[v[i]].push_back(u[i]);
        maxG[u[i]].push_back(v[i]);
    }
    for (int j = 1; j <= n - 2; j++) {
        ans += c * j * (1ULL * (n + j) * (n - j - 1) / 2);
        ans += b * j * j * (n - j - 1);
    }
    for (int i = 0; i <= n - 3; i++) {
        ans += a * i * (1ULL * (n - 3 - i + 1 + 1) * (n - 3 - i + 1) / 2);
    }
    for (int i = 0; i < m; i++) {
        int u = ::u[i], v = ::v[i];
        ans -= a * (0 + u - 1) * u / 2;
        ans -= b * u * u;
        ans -= c * v * u;

        ans -= a * u * (v - u - 1);
        ans -= b * (u + 1 + v - 1) * (v - u - 1) / 2;
        ans -= c * v * (v - u - 1);

        ans -= a * u * (n - 1 - v);
        ans -= b * v * (n - 1 - v);
        ans -= c * (v + 1 + n - 1) * (n - 1 - v) / 2;
    }
    for (int i = 0; i < n; i++) { sort(minG[i].begin(), minG[i].end()); }
    for (int u = 0; u < n; u++) {
        for (int i = 1; i < minG[u].size(); i++) { sum[i] = sum[i - 1] + minG[u][i - 1]; }
        for (int i = 1; i < minG[u].size(); i++) {
            int v = minG[u][i];
            ans += a * sum[i] + b * v * i + c * u * i;
        }
    }
    for (int i = 0; i < n; i++) { sort(maxG[i].begin(), maxG[i].end()); }
    for (int u = 0; u < n; u++) {
        for (int i = 1; i < maxG[u].size(); i++) { sum[i] = sum[i - 1] + maxG[u][i - 1]; }
        for (int i = 1; i < maxG[u].size(); i++) {
            int v = maxG[u][i];
            ans += a * u * i + b * sum[i] + c * v * i;
        }
    }
    for (int u = 0; u < n; u++) {
        sum[u] = 0;
        for (int v : maxG[u]) { sum[u] += v; }
    }
    for (int u = 0; u < n; u++) {
        for (int v : maxG[u]) {
            ans += a * u * maxG[v].size() + b * v * maxG[v].size() + c * sum[v];
        }
    }
    for (int i = 0; i < n; i++) { minG[i].clear(); }
    for (int i = 0; i < m; i++) {
        if (make_pair(degree[u[i]], u[i]) >= make_pair(degree[v[i]], v[i])) { swap(u[i], v[i]); }
        minG[u[i]].push_back(v[i]);
    }
    for (int u = 0; u < n; u++) {
        for (int v : minG[u]) { vis[v] = true;}
        for (int v : minG[u]) {
            for (int w : minG[v]) {
                if (!vis[w]) { continue; }
                int node[3] = {u, v, w};
                sort(node, node + 3);
                ans -= a * node[0] + b * node[1] + c * node[2];
            }
        }
        for (int v : minG[u]) { vis[v] = false; }
    }
    cout << ans << endl;
	return 0;
}