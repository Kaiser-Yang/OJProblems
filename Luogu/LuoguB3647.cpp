// problem statement: https://www.luogu.com.cn/problem/B3647

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;
constexpr int MAXM = 4510;

int n, m, u, v, w;
int g[MAXN][MAXN];

int main()
{
	ios::sync_with_stdio(false);
    memset(g, 0x3f, sizeof(g));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { g[i][i] = 0; }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[v][u] = g[u][v] = min(g[u][v], w);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
	return 0;
}
