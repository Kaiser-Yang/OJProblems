#include <bits/stdc++.h>

using namespace std;

constexpr int MAXP = 510;

int s, p;

using Node = pair<int, int>;

Node node[MAXP];
int g[MAXP][MAXP];
vector<int> ans;

int getDis(const Node &a, const Node &b)
{
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) *(a.second - b.second);
}

void prim()
{
    vector<int> dis(p, numeric_limits<int>::max());
    vector<bool> vis(p, false);
    for (int i = 0; i < p; i++) { dis[i] = g[i][0]; }
    vis[0] = true;
    int node = -1;
    for (int i = 1; i < p; i++) {
        node = -1;
        for (int j = 0; j < p; j++) {
            if (vis[j]) { continue; }
            if (node == -1 || dis[j] < dis[node]) { node = j; }
        }
        vis[node] = true;
        ans.push_back(dis[node]);
        for (int j = 0; j < p; j++) { dis[j] = min(dis[j], g[node][j]); }
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> s >> p;
    for (int i = 0; i < p; i++) { cin >> node[i].first >> node[i].second; }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            g[i][j] = getDis(node[i], node[j]);
        }
    }
    prim();
    sort(ans.begin(), ans.end(), greater<int>());
    cout << fixed << setprecision(2) << sqrt(ans[s - 1]) << endl;
	return 0;
}
