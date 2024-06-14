// problem statement: https://www.luogu.com.cn/problem/P2504
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;
constexpr int MAXM = 510;

int n, m, maxDis;
int capability[MAXM];

using Node = pair<int, int>;

Node node[MAXN];
int g[MAXN][MAXN];

int getDis(const Node &a, const Node &b)
{
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) *(a.second - b.second);
}

void prim()
{
    vector<int> dis(MAXN, numeric_limits<int>::max());
    vector<bool> vis(MAXN, false);
    for (int i = 0; i < n; i++) { dis[i] = g[i][0]; }
    vis[0] = true;
    for (int i = 1; i < n; i++) {
        int node = -1;
        for (int i = 0; i < n; i++) {
            if (vis[i]) { continue; }
            if (node == -1 || dis[i] < dis[node]) { node = i; }
        }
        vis[node] = true;
        maxDis = max(maxDis, dis[node]);
        for (int i = 0; i < n; i++) { dis[i] = min(dis[i], g[node][i]); }
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> m;
    for (int i = 0; i < m; i++) { cin >> capability[i]; capability[i] *= capability[i]; }
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> node[i].first >> node[i].second; }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = getDis(node[i], node[j]);
        }
    }
    prim();
    cout << count_if(capability, capability + m, [](auto c){ return c >= maxDis; }) << endl;
	return 0;
}
