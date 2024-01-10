#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int cnt;
int in[MAXN]; // in[i]: i-th node's full dfs id when it enters dfs.
int out[MAXN]; // out[i]: i-th node's full dfs id when it leaves dfs.
int nodeId[MAXN * 2]; // nodeId[i]: a node id whose full dfs id i.
long long dis[MAXN]; // dis[i]: the dis between i-th node and 1-st node.

int ecnt;
int head[MAXN];

int n, q, d;
int u[MAXN], v[MAXN], parent[MAXN];
long long last, e;
long long w[MAXN];

struct Edge
{
	int to, nex;
	long long w;
} es[MAXN << 1];

struct TreeNode
{
	int left, right;
	long long maxDepth = 0; // max left <= a <= right (dis[a])
	long long minDepth =    // min left <= a <= right (dis[a])
		numeric_limits<long long>::max();
	long long ans = 0;      // max left <= l <= a <= r <= right (dis[l] + dis[r] - 2dis[a])
	long long maxRight = 0; // max left <= a <= r <= right (dis[a] - 2dis[r])
	long long maxLeft = 0;  // max left <= r <= a <= right (dis[a] - 2dis[r])
	long long lazy = 0;
} tr[MAXN << 3];

int lc(int id) { return id << 1; }

int rc(int id) { return id << 1 | 1; }

void pushup(int id)
{
	int lc = ::lc(id), rc = ::rc(id);
	tr[id].ans = max({tr[lc].ans, tr[rc].ans, tr[lc].maxRight + tr[rc].maxDepth, tr[lc].maxDepth + tr[rc].maxLeft});
	tr[id].minDepth = min(tr[lc].minDepth, tr[rc].minDepth);
	tr[id].maxDepth = max(tr[lc].maxDepth, tr[rc].maxDepth);
	tr[id].maxRight = max({tr[lc].maxRight, tr[rc].maxRight, tr[lc].maxDepth - 2 * tr[rc].minDepth});
	tr[id].maxLeft = max({tr[lc].maxLeft, tr[rc].maxLeft, tr[rc].maxDepth - 2 * tr[lc].minDepth});
}

void build(int id, int l, int r)
{
	tr[id].left = l;
	tr[id].right = r;
	if (l == r) {
		tr[id].maxDepth = tr[id].minDepth = dis[nodeId[l]];
		tr[id].maxRight = tr[id].maxLeft = -dis[nodeId[l]];
		tr[id].ans = tr[id].lazy = 0;
		return;
	}
	int mid = l + r >> 1;
	build(lc(id), l, mid);
	build(rc(id), mid + 1, r);
	pushup(id);
}

void update(int id, long long delta)
{
	tr[id].minDepth += delta;
	tr[id].maxDepth += delta;
	tr[id].maxRight -= delta;
	tr[id].maxLeft  -= delta;
	tr[id].lazy     += delta;
}

void pushdown(int id)
{
	update(lc(id), tr[id].lazy);
	update(rc(id), tr[id].lazy);
	tr[id].lazy = 0;
}

void update(int id, int l, int r, long long delta)
{
	if (tr[id].left >= l && tr[id].right <= r) {
		update(id, delta);
		return;
	}
	pushdown(id);
	int mid = (tr[id].left + tr[id].right) >> 1;
	if (l <= mid) { update(lc(id), l, r, delta); }
	if (mid < r) { update(rc(id), l, r, delta); }
	pushup(id);
}

void dfs(int u, int par)
{
	parent[u] = par;
	nodeId[++cnt] = u;
	in[u] = cnt;
	for (int i = head[u]; i != -1; i = es[i].nex) {
		int v = es[i].to;
		if (v == par) { continue; }
		dis[v] = dis[u] + es[i].w;
		dfs(v, u);
		nodeId[++cnt] = u;
	}
	out[u] = cnt;
}

void addEdge(int u, int v, long long w)
{
	es[ecnt].to = v;
	es[ecnt].w = w;
	es[ecnt].nex = head[u];
	head[u] = ecnt++;
}

int main()
{
	ios::sync_with_stdio(false);
	memset(head, -1, sizeof(head));
	cin >> n >> q >> w[0];
	for (int i = 1; i < n; i++) {
		cin >> u[i] >> v[i] >> w[i];
		addEdge(u[i], v[i], w[i]);
		addEdge(v[i], u[i], w[i]);
	}
	dfs(1, 0);
	build(1, 1, cnt);
	while (q--) {
		cin >> d >> e;
		d = (d % (n - 1) + last % (n - 1)) % (n - 1) + 1;
		e = (e % w[0] + last % w[0]) % w[0];
		long long delta = e - w[d];
		if (parent[u[d]] == v[d]) { update(1, in[u[d]], out[u[d]], delta); }
		if (parent[v[d]] == u[d]) { update(1, in[v[d]], out[v[d]], delta); }
		w[d] = e;
		last = tr[1].ans;
		cout << last << endl;
	}
	return 0;
}
