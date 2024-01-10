#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 10;

int n, s, u, v, w, ecnt, node1, node2, fathest;
int head[MAXN], dis[MAXN], parent[MAXN], dis1[MAXN], dis2[MAXN];
bool onDiameter[MAXN];

vector<int> diameterNode;

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

void bfs(int s, int *dis)
{
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	int res = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i != -1; i = es[i].nex) {
			int v = es[i].to;
			if (dis[v] != -1 || onDiameter[v]) { continue; }
			dis[v] =dis[u] + es[i].w;
			if (onDiameter[s]) { res = max(res, dis[v]); }
			q.push(v);
		}
	}
	if (onDiameter[s]) { dis[s] = res; }
}

void bfs()
{
	// get the diameter end nodes: node1 and node2
	dis[fathest] = -1; // because the weight of one edge can be zero.
	fathestNode(1, 0);
	node1 = fathest;
	fathest = 0;
	dis[fathest] = -1;
	fathestNode(node1, 0);
	node2 = fathest;

	// get the dis1 ans dis2;
	memset(dis1, -1, sizeof(dis1));
	bfs(node1, dis1);
	memset(dis2, -1, sizeof(dis2));
	bfs(node2, dis2);

	// get the dis.
	int now = node2;
	do {
		diameterNode.push_back(now);
		onDiameter[now] = true;
	} while ((now = parent[now]) != 0);
	reverse(diameterNode.begin(), diameterNode.end());
	memset(dis, -1, sizeof(dis));
	for (int node : diameterNode) {
		bfs(node, dis);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	memset(head, -1, sizeof(head));
	cin >> n >> s;
	for (int i = 1; i < n; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	bfs(); // get the distance:
		   // dis1[i]: the distance between node i and node1.
		   // dis2[i]: the distance between node i and node2.
		   // dis[i] : the maximum distance from diameter node i to a non-diameter node cross no any other diameter node.
	int l = 0, r = 0, ans = numeric_limits<int>::max();
	deque<pair<int, int>> dq(diameterNode.size());
	while (l < diameterNode.size()) {
		while (r < diameterNode.size() && dis1[diameterNode[r]] - dis1[diameterNode[l]] <= s) {
			while (!dq.empty() && dq.back().second <= dis[diameterNode[r]]) { dq.pop_back(); }
			dq.push_back({r, dis[diameterNode[r]]});
			ans = min(ans, max({dis1[diameterNode[l]], dis2[diameterNode[r]], dq.front().second}));
			r++;
		}
		if (!dq.empty() && dq.back().first == l) { dq.pop_front(); }
		l++;
		if (l > r) { r = l; }
	}
	cout << ans << endl;
	return 0;
}