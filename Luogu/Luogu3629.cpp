#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 10;

int n, k, u, v, ecnt, node1, node2, fathest, ans, diameter;
int head[MAXN], maxPath[MAXN], subMaxPath[MAXN], parent[MAXN], dis[MAXN];
bool onDiameter[MAXN];

struct addEdge
{
	int to, nex, w;
} es[MAXN << 1];

void addEdge(int u, int v, int w)
{
	es[ecnt].to = v;
	es[ecnt].nex = head[u];
	es[ecnt].w = w;
	head[u] = ecnt++;
}

void fathestNode(int u, int par)
{
	parent[u] = par;
	for (int i = head[u]; i != -1; i = es[i].nex) {
		int v = es[i].to;
		if (v == par) { continue; }
		dis[v] = dis[u] + es[i].w;
		if (dis[v] > dis[fathest]) {
			fathest = v;
		}
		fathestNode(v, u);
	}
}

void dfs(int u, int par)
{
	for (int i = head[u]; i != -1; i = es[i].nex) {
		int v = es[i].to;
		if (onDiameter[v] && onDiameter[u]) { es[i].w = -1; }
		if (v == par) { continue; }
		dfs(v, u);
		if (maxPath[v] + es[i].w > maxPath[u]) {
			subMaxPath[u] = maxPath[u];
			maxPath[u] = maxPath[v] + es[i].w;
		} else if (maxPath[v] + es[i].w > subMaxPath[u]) {
			subMaxPath[u] = maxPath[v] + es[i].w;
		}
	}
	diameter = max(diameter, maxPath[u] + subMaxPath[u]);
}

int main()
{
	ios::sync_with_stdio(false);
	memset(head, -1, sizeof(head));
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		addEdge(u, v, 1);
		addEdge(v, u, 1);
	}
	ans = 2 * (n - 1);
	fathestNode(1, 0);
	node1 = fathest;
	dis[fathest] = 0;
	fathestNode(node1, 0);
	node2 = fathest;
	ans -= dis[node2] - 1;
	if (k == 1) {
		cout << ans << endl;
		return 0;
	}
	int now = node2;
	do {
		onDiameter[now] = true;
	} while ((now = parent[now]) != 0);
	dfs(1, 0);
	ans -= diameter - 1;
	cout << ans << endl;
	return 0;
}
