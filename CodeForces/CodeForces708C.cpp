#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 4e5 + 10;

int n, u, v, centroid;
int size[MAXN];
bool ans[MAXN];

vector<int> g[MAXN];
vector<pair<int, int>> subTreeSize;

void findCentroid(int u, int par)
{
    size[u] = 1;
    int maxSonSize = 0;
    for (int v : g[u]) {
        if (v == par) { continue; }
        findCentroid(v, u);
        size[u] += size[v];
        maxSonSize = max(maxSonSize, size[v]);
    }
    if (maxSonSize <= n / 2 && n - size[u] <= n / 2) { centroid = u; }
}

void placeAns(int u, int par, int fromWhich, int nodeNum)
{
    if (nodeNum <= n / 2) { ans[u] = true; }
    for (int i = 0; i < 2 && i < subTreeSize.size(); i++) {
        if (ans[u]) { break; }
        if (subTreeSize[i].second == fromWhich) { continue; }
        if (n - size[u] - subTreeSize[i].first <= n / 2) { ans[u] = true; }
        else { break; }
    }
    for (int v : g[u]) {
        if (v == par) { continue; }
        placeAns(v, u, fromWhich, nodeNum);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    findCentroid(1, 0);
    ans[centroid] = true;
    findCentroid(centroid, 0); // caculate size when centroid is as root.
    for (int v : g[centroid]) { subTreeSize.push_back({size[v], v}); }
    sort(subTreeSize.begin(), subTreeSize.end(), greater<pair<int, int>>());
    for (auto item : subTreeSize) { placeAns(item.second, centroid, item.second, n - item.first); }
    for_each(ans + 1, ans + 1 + n, [] (bool val) { cout << val << " "; });
    cout << endl;
	return 0;
}
