#include <bits/stdc++.h>

using namespace std;

int dp(int s, vector<int> &d, vector<vector<int>> &g, vector<bool> &reachable, vector<int> &pre) {
    int &ans = d[s];
    if (ans != -1) { return ans; }
    if (s == 0) {
        ans = 0;
        return ans;
    }
    ans = numeric_limits<int>::max() / 2;
    for (int sub = s; sub != 0; sub = (sub - 1) & s) {
        if (reachable[sub]) { continue; }
        if (dp(s ^ sub, d, g, reachable, pre) + 1 < ans) {
            ans = d[s ^ sub] + 1;
            pre[s] = s ^ sub;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int n, cnt;
    vector<pair<char, char>> resource;
    vector<vector<int>> g;
    vector<bool> reachable;
    vector<int> d, pre;
    map<char, int> id;
    while (cin >> n) {
        resource.clear();
        g.clear();
        g.resize(15);
        reachable.clear();
        reachable.resize(1 << 15, false);
        id.clear();
        d.clear();
        d.resize(1 << 15, -1);
        pre.resize(1 << 15);
        cnt = 0;
        for (int i = 0; i < n; i++) {
            string a, b;
            cin >> a >> b;
            if (!id.count(a[0])) {
                id[a[0]] = cnt;
                cnt++;
            }
            if (!id.count(b[0])) {
                id[b[0]] = cnt;
                cnt++;
            }
            int u = id[a[0]], v = id[b[0]];
            g[u].push_back(v);
            g[v].push_back(u);
            resource.push_back({a[0], b[0]});
            for (int s = 0; s < (1 << 15); s++) {
                if (s & (1 << u) && s & (1 << v)) { reachable[s] = true; }
            }
        }
        cout << dp((1 << id.size()) - 1, d, g, reachable, pre) - 2 << endl;
        vector<int> depth(15);
        cnt = 0;
        for (int s = (1 << id.size()) - 1; s != 0; s = pre[s]) {
            for (int i = 0; i < 15; i++) {
                if (s & (1 << i)) { depth[i] = cnt; }
            }
            cnt++;
        }
        for (int i = 0; i < n; i++) {
            if (depth[id[resource[i].first]] > depth[id[resource[i].second]]) {
                swap(resource[i].first, resource[i].second);
            }
            cout << resource[i].first << " " << resource[i].second << endl;
        }
    }
    return 0;
}