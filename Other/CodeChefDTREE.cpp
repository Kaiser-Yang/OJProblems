// problem statement: https://www.codechef.com/problems/DTREE?tab=statement

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int T, n, u, v, fathest, node1, node2;

vector<int> g[MAXN];
int depth[MAXN], maxPath[MAXN], subMaxPath[MAXN], ans[MAXN], diameter[MAXN], parent[MAXN];
bool onDiameter[MAXN];

void fathestNode(int u, int par)
{
	parent[u] = par;
	depth[u] = depth[par] + 1;
	if (depth[u] > depth[fathest]) {
		fathest = u;
	}
	for (int v : g[u]) {
		if (v == par) { continue; }
		fathestNode(v, u);
	}
}

void dfs(int u, int par)
{
	for (int v : g[u]) {
		if (v == par) { continue; }
		dfs(v, u);
		if (maxPath[v] + 1 > maxPath[u]) {
			subMaxPath[u] = maxPath[u];
			maxPath[u] = maxPath[v] + 1;
		} else if (maxPath[v] + 1 > subMaxPath[u]) {
			subMaxPath[u] = maxPath[v] + 1;
		}
		ans[u] = max(ans[u], diameter[v]);
		diameter[u] = max(diameter[u], diameter[v]);
	}
	diameter[u] = max(diameter[u], maxPath[u] + subMaxPath[u]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) { g[i].clear(); }
		for (int i = 1; i < n; i++) {
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		fathest = 1;
		fathestNode(1, 0);
		node1 = fathest; // one end node of diameter.
		memset(parent, 0, sizeof(parent));
		fathestNode(node1, 0);
		node2 = fathest; // the other end node of diameter.
		memset(onDiameter, false, sizeof(onDiameter));
		int now = node2;
		do {
			onDiameter[now] = true;
		} while ((now = parent[now]) != 0);
		memset(ans, 0, sizeof(ans));
		memset(diameter, 0, sizeof(diameter));
		memset(maxPath, 0, sizeof(maxPath));
		memset(subMaxPath, 0, sizeof(subMaxPath));
		dfs(node1, 0);
		memset(diameter, 0, sizeof(diameter));
		memset(maxPath, 0, sizeof(maxPath));
		memset(subMaxPath, 0, sizeof(subMaxPath));
		dfs(node2, 0);
		for (int i = 1; i <= n; i++) {
			if (onDiameter[i]) {
				cout << ans[i] << " ";
			} else {
				cout << depth[node2] - 1 << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
