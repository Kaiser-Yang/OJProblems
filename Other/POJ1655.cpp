// NOTICE: POJ only supports C++ 98
#include <vector>
#include <iostream>

using namespace std;

const int MAXN = 2e4 + 10;

int T, n, u, v, ans;
int size[MAXN];

vector<int> g[MAXN], centroid;

void dfs(int u, int par)
{
    size[u] = 1;
    int maxSonSize = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == par) { continue; }
        dfs(v, u);
        size[u] += size[v];
        maxSonSize = max(maxSonSize, size[v]);
    }
    if (maxSonSize <= n / 2 && n - size[u] <= n / 2) {
        if (centroid.size() == 0) { ans = max(maxSonSize, n - size[u]); }
        else if (ans < max(maxSonSize, n - size[u])) { return; }
        else if (ans > max(maxSonSize, n - size[u])) {
            ans = max(maxSonSize, n - size[u]);
            centroid.pop_back();
        }
        centroid.push_back(u);
    }
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
        centroid.clear();
        dfs(1, 0);
        if (centroid.size() == 2 && centroid[1] < centroid[0]) {
            swap(centroid[0], centroid[1]);
        }
        cout << centroid[0] << " " << ans << endl;
    }
	return 0;
}
