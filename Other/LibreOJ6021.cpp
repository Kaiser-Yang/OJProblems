#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 7e4 + 10;
constexpr int MAXM = 1e5 + 10;
constexpr int  MOD = 1e9 + 7;

int n, m, cnt, ans, q, u, v;
int h[MAXN << 1], in[MAXN << 1], nodeId[MAXN << 2], depth[MAXN << 1], val[MAXN << 1], lg[MAXN << 2], st[MAXN << 2][20];

vector<int> g[MAXN << 1];

struct Edge
{
    int u, v, w;
} edge[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

void addEdge(int u, int v)
{
    g[u].push_back(v);
}

int A, B, C, P;

int rnd()
{
    return A = (A * B + C) % P;
}

void dfs(int u, int par)
{
    // cout << u << " " << par << " " << val[u] << endl;
    depth[u] = depth[par] + 1;
    nodeId[++cnt] = u;
    in[u] = cnt;
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
        nodeId[++cnt] = u;
    }
}

void sparseTableInit()
{
    for (int i = 2; i <= cnt; i++) { lg[i] = lg[i / 2] + 1; }
    for (int i = 1; i <= cnt; i++) { st[i][0] = nodeId[i]; }
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
            st[i][j] = depth[st[i][j - 1]] < depth[st[i + (1 << (j - 1))][j - 1]] ?
                       st[i][j - 1] :
                       st[i + (1 << (j - 1))][j - 1];
        }
    }
}

int query(int l, int r)
{
    if (l > r) { swap(l, r); }
    int j = lg[r - l + 1];
    return val[depth[st[l][j]] < depth[st[r - (1 << j) + 1][j]] ?
               st[l][j] :
               st[r - (1 << j) + 1][j]];
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= 2 * n - 1; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [] (const auto &a, const auto &b) { return a.w < b.w; });
    int tempN = n;
    for (int i = 0; i < m; i++) {
        int fa = find(edge[i].u), fb = find(edge[i].v);
        if (fa == fb) { continue; }
        n++;
        h[fa] = h[fb] = n;
        addEdge(fa, n);
        addEdge(n, fa);
        addEdge(fb, n);
        addEdge(n, fb);
        val[n] = edge[i].w;
        if (cnt == tempN - 1) { break; }
    }
    cnt = 0;
    // cout << n << endl;
    dfs(n, 0);
    sparseTableInit();
    cin >> q;
    cin >> A >> B >> C >> P;
    for (int i = 0; i < q; i++) {
        u = rnd() % tempN + 1, v = rnd() % tempN + 1;
        // cout << u << " " << v << " " << in[u] << " " << in[v] << " " << query(in[u], in[v]) << endl;
        ans = (ans + query(in[u], in[v])) % MOD;
    }
    cout << ans << endl;
	return 0;
}
