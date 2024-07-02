// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 6e3 + 10;

int n, root;
int happiness[MAXN], parent[MAXN], dp[MAXN][2];
vector<int> g[MAXN];

void addEdge(int u, int v)
{
	g[u].emplace_back(v);
}

void dfs(int u)
{
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		dfs(v);
		sum1 += max(dp[v][0], dp[v][1]);
		sum2 += dp[v][0];
	}
	dp[u][0] = sum1;
	dp[u][1] = sum2 + happiness[u];
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> happiness[i]; }
	for (int i = 1; i < n; i++) {
		int k, l;
		cin >> l >> k;
		parent[l] = k;
		addEdge(k, l);

	}
	for (int i = 1; i <= n; i++) {
		if (parent[i] == 0) {
			root = i;
			break;
		}
	}
	dfs(root);
	cout << max(dp[root][0], dp[root][1]) << endl;
	return 0;
}