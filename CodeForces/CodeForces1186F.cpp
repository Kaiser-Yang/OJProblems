// problem statement: https://codeforces.com/problemset/problem/1186/F

#include <bits/stdc++.h>

using namespace std;

int n, m, cnt;
vector<int> head, degree, f, num;
vector<int> id;

vector<pair<int, int> > ans;

struct Edge {
    int to, nex;
    bool vis;
    Edge(int to, int nex, bool vis) : to(to), nex(nex), vis(vis) {}
};
vector<Edge> es;

void addedge(int u, int v) {
    es.emplace_back(v, head[u], false);
    head[u] = es.size() - 1;
}

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

void join(int a, int b) {
    int x = find(a);
    int y = find(b);
    f[x] = y;
}

void dfs(int u) {
    num[u]++;
    int now_num = num[u];
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        head[u] = es[i].nex;
        if (es[i].vis) { continue; }
        es[i].vis = es[i ^ 1].vis = true;
        dfs(v);
        if (num[u] > now_num) { break; }
    }
    id[++cnt] = u;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    head.resize(n + 2, -1);
    degree.resize(n + 2, 0);
    f.resize(n + 2, 0);
    id.resize(n + m + 2, 0);
    num.resize(n + 2, 0);
    for (int i = 1; i <= n + 1; i++) { f[i] = i; }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++, degree[v]++;
        join(u, v);
        addedge(u, v);
        addedge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (degree[i] & 1) {
            addedge(n + 1, i);
            addedge(i, n + 1);
            join(n + 1, i);
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        if (f[i] == i && head[i] != -1) { dfs(i); }
    }
    for (int i = 1; i < cnt; i += 2) {
        if (id[i] == n + 1 || id[i + 1] == n + 1) { continue; }
        ans.emplace_back(id[i], id[i + 1]);
    }
    for (int i = 2; i < cnt; i += 2) {
        if (id[i] == n + 1 || id[i + 1] == n + 1) { continue; }
        if (id[i - 1] != n + 1 && (i + 2 <= cnt && id[i + 2] != n + 1)) { continue; }
        ans.emplace_back(id[i], id[i + 1]);
    }
    cout << ans.size() << '\n';
    for (auto &&[u, v] : ans) { cout << u << ' ' << v << '\n'; }
    return 0;
}
