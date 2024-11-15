// problem statement: https://www.luogu.com.cn/problem/P2680

#include <bits/stdc++.h>

constexpr int MAXN = 3e5 + 10;
constexpr int MAXM = 3e5 + 10;

using namespace std;

int n, m, u, v, w;
int head[MAXN], ecnt;

struct edge {
    int to, next, w;
} es[MAXN << 1];

void add_edge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].next = head[u];
    head[u] = ecnt++;
}

struct carriage {
    int u, v, lca, dis;
} car[MAXM];

constexpr int root = 1;
int dis[MAXN], par[MAXN][20], depth[MAXN];

void build(int u, int fa) {
    for (int i = head[u]; ~i; i = es[i].next) {
        int v = es[i].to;
        if (v == fa) continue;
        dis[v] = dis[u] + es[i].w;
        par[v][0] = u;
        depth[v] = depth[u] + 1;
        for (int j = 1; j < 20; j++) { par[v][j] = par[par[v][j - 1]][j - 1]; }
        build(v, u);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) {
        if (depth[par[a][i]] >= depth[b]) { a = par[a][i]; }
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}

int get_dis(int a, int b, int lca) { return dis[a] + dis[b] - 2 * dis[lca]; }

void dfs(int u, int fa, vector<int> &cnt) {
    for (int i = head[u]; ~i; i = es[i].next) {
        int v = es[i].to;
        if (v == fa) continue;
        dfs(v, u, cnt);
        cnt[u] += cnt[v];
    }
}

bool check(int ans) {
    int exceed_cnt = 0;
    vector<int> difference_cnt(n + 1, 0);
    int max_exceed = 0;
    for (int i = 0; i < m; i++) {
        if (car[i].dis > ans) {
            max_exceed = max(max_exceed, car[i].dis - ans);
            difference_cnt[car[i].u]++;
            difference_cnt[car[i].v]++;
            difference_cnt[car[i].lca] -= 2;
            exceed_cnt++;
        }
    }
    if (exceed_cnt == 0) { return true; }
    dfs(1, 0, difference_cnt);
    for (int i = 2; i <= n; i++) {
        if (difference_cnt[i] >= exceed_cnt && get_dis(i, par[i][0], par[i][0]) >= max_exceed) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    build(root, 0);
    int l = 0, r = 0;
    for (int i = 0; i < m; i++) {
        cin >> car[i].u >> car[i].v;
        car[i].lca = lca(car[i].u, car[i].v);
        car[i].dis = get_dis(car[i].u, car[i].v, car[i].lca);
        r = max(r, car[i].dis);
    }
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}
