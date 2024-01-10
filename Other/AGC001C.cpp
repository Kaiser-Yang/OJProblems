// problem statement: https://atcoder.jp/contests/agc001/tasks/agc001_c

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2010;

int n, k, ans = numeric_limits<int>::max();
int u[MAXN], v[MAXN], depth[MAXN];

vector<int> g[MAXN];

void dfs(int u, int par)
{
	depth[u] = depth[par] + 1;
	for (int v : g[u]) {
		if (v == par) { continue; }
		dfs(v, u);
	}
}

int count()
{
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (depth[i] > k / 2) { res++; }
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		cin >> u[i] >> v[i];
		g[u[i]].push_back(v[i]);
		g[v[i]].push_back(u[i]);
	}
	if (k % 2 == 0) {
		depth[0] = -1;
		for (int i = 1; i <= n; i++) {
			dfs(i, 0);
			ans = min(ans, count());
		}
	} else {
		int temp = 0, now = 0;
		for (int i = 1; i < n; i++) {
			depth[v[i]] = -1;
			dfs(u[i], v[i]);
			temp = depth[u[i]];
			depth[u[i]] = -1;
			dfs(v[i], u[i]);
			depth[u[i]] = temp;
			ans = min(ans, count());
		}
	}
	cout << ans << endl;
	return 0;
}
