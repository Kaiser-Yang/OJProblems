// problem statement: https://loj.ac/p/10085
// Tag: having been in my blog

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 510;
const int INF  = 0x3f3f3f3f;

int T, m1, m2, n, u, v, w;
int d[MAXN];

struct Edge
{
    int to, w;
    Edge(int to, int w) : to(to), w(w) {}
};

vector<Edge> g[MAXN];

// return if has negative circle
bool bellmanFord()
{
    memset(d, 0x3f, sizeof(int) * (n + 1));
    d[0] = 0;
    bool flag = false;
    for (int i = 0; i <= n; i++) {
        flag = false;
        for (int u = 0; u <= n; u++) {
            if (d[u] == INF) { continue; }
            for (int j = 0; j < g[u].size(); j++) {
                int v = g[u][j].to, w = g[u][j].w;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    flag = true;
                }
            }
        }
        if (!flag) { return false; }
    }
    return flag;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m1 >> m2;
        for (int i = 0; i <= n; i++) { g[i].clear(); }
        for (int i = 0; i < m1; i++) {
            cin >> u >> v >> w;
            g[u].push_back(Edge(v, w));
            g[v].push_back(Edge(u, w));
        }
        for (int i = 0; i < m2; i++) {
            cin >> u >> v >> w;
            w = -w;
            g[u].push_back(Edge(v, w));
        }
        for (int i = 1; i <= n; i++) { g[0].push_back(Edge(i, 0)); }
        cout << (bellmanFord() ? "YES\n" : "NO\n");
    }
	return 0;
}
