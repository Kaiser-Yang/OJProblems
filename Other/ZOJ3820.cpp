// problem statement:
// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369872?type=7&page=0

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int T, n, u, v, l, r, mid, node1, node2, ans1Temp, ans2Temp, ans1, ans2;
int depth[MAXN], dis1[MAXN], dis2[MAXN], parent[MAXN];

vector<int> g[MAXN];

// search from s whthin limit depth or return the fathest node from s.
int bfs(int s, int *dis, bool updateParent = false) {
    queue<int> q;
    q.push(s);
    int fathest = s;
    dis[s]      = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dis[v] != -1) { continue; }
            dis[v] = dis[u] + 1;
            if (updateParent) { parent[v] = u; }
            if (dis[v] > dis[fathest]) { fathest = v; }
            q.push(v);
        }
    }
    return fathest;
}

bool check(int ans) {
    ans1Temp = node2;
    for (int i = 0; i < ans; i++) {
        ans1Temp = parent[ans1Temp];
        if (ans1Temp == 0) {
            ans2Temp = ans1Temp = 1;
            return true;
        }
    }
    ans2Temp = node2;
    for (int i = 0; i < depth[node2] - ans; i++) { ans2Temp = parent[ans2Temp]; }
    if (ans2Temp == 0) { ans2Temp = ans1Temp; }
    memset(dis1, -1, sizeof(int) * (n + 1));
    bfs(ans1Temp, dis1);
    memset(dis2, -1, sizeof(int) * (n + 1));
    bfs(ans2Temp, dis2);
    for (int i = 1; i <= n; i++) {
        if (min(dis1[i], dis2[i]) > ans) { return false; }
    }
    return true;
}

int main() {
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
        memset(depth, -1, sizeof(int) * (n + 1));
        node1 = bfs(1, depth);
        memset(depth, -1, sizeof(int) * (n + 1));
        node2 = bfs(node1, depth, true);
        l = 0, r = n, mid = 0;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid)) {
                ans1 = ans1Temp;
                ans2 = ans2Temp;
                r    = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (ans1 == ans2) {
            if (ans1 == 1) {
                ans2 = 2;
            } else {
                ans1 = 1;
            }
        }
        cout << l << " " << ans1 << " " << ans2 << endl;
    }
    return 0;
}
