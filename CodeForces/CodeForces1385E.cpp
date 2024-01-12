#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int T, n, m;
int type, u, v;
int inDegree[MAXN], id[MAXN];
vector<pair<int, int>> edge;
vector<int> g[MAXN];

bool toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++) { if (inDegree[i] == 0) { q.push(i); } }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        id[u] = cnt;
        for (int v : g[u]) { if (--inDegree[v] == 0) { q.push(v); } }
    }
    return cnt == n;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        edge.clear();
        for_each(g + 1, g + n + 1, [] (auto &val) { val.clear(); });
        memset(inDegree + 1, 0, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> type >> u >> v;
            if (type == 0) { edge.push_back({u, v}); }
            else {
                edge.push_back({u, v});
                g[u].push_back(v);
                inDegree[v]++;
            }
        }
        if (toposort()) {
            cout <<"YES\n";
            for (auto item : edge) {
                if (id[item.first] < id[item.second]) {
                    cout << item.first << " " << item.second << endl;
                } else {
                    cout << item.second << " " << item.first << endl;
                }
            }
        } else {
            cout << "NO\n";
        }
    }
	return 0;
}
