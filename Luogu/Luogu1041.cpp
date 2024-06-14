// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 310;

int n, m, u, v, ecnt, ans = MAXN, maxDepth;
int head[MAXN], depth[MAXN], par[MAXN], siz[MAXN];
vector<int> depthNode[MAXN];
bool cut[MAXN];

struct Edge
{
	int to, nex;
}es[MAXN * 2];

void addEdge(int u, int v)
{
	es[ecnt].to = v;
	es[ecnt].nex = head[u];
	head[u] = ecnt++;
}

void getDepth(int u, int fa)
{
	depth[u] = depth[fa] + 1;
	par[u] = fa;
	siz[u] = 1;
	for (int i = head[u]; i != -1; i = es[i].nex) {
		int v = es[i].to;
		if (v == fa) { continue; }
		getDepth(v, u);
		siz[u] += siz[v];
	}
}

void dfs(int nowDepth, int patientNum)
{
	if (nowDepth == maxDepth + 1) {
		ans = min(ans, patientNum);
	}
	for (int i = 0; i < depthNode[nowDepth].size(); i++) {
		if (cut[par[depthNode[nowDepth][i]]]) {
			cut[depthNode[nowDepth][i]] = true;
		} else {
			cut[depthNode[nowDepth][i]] = false;
		}
	}
	bool done = true;
	for (int i = 0; i < depthNode[nowDepth].size(); i++) {
		if (!cut[depthNode[nowDepth][i]]) {
			done = false;
		}
	}
	if (done) {
		ans = min(ans, patientNum);
		return;
	}
	for (int i = 0; i < depthNode[nowDepth].size(); i++) {
		int v = depthNode[nowDepth][i];
		if (cut[v]) { continue; }
		cut[v] = true;
		dfs(nowDepth + 1, patientNum - siz[v]);
		cut[v] = false;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	memset(head, -1, sizeof(head));
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	getDepth(1, 0);
	for (int i = 1; i <= n; i++) {
		depthNode[depth[i]].emplace_back(i);
		maxDepth = max(maxDepth, depth[i]);
	}
	dfs(2, n);
	cout << ans << endl;

	return 0;
}
