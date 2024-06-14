// problem statement: https://www.luogu.com.cn/problem/P5908

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int n, d, u, v;
int dis[MAXN];

vector<int> g[MAXN];

void dfs(int u, int par)
{
    dis[u] = dis[par] + 1;
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = -1;
    dfs(1, 0);
    cout << count_if(dis + 2, dis + 1 + n, [] (auto val) { return val <= d; }) << endl;
	return 0;
}
