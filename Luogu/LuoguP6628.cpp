// problem statement: https://www.luogu.com.cn/problem/P6628
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2510;

int n, m, s, u, v, ans;
int degree[MAXN];

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) { return w < other.w; }
};

vector<Edge> edge;

struct UFS {
    int h[MAXN];

    void init(int n) {
        for (int i = 0; i <= n; i++) { h[i] = i; }
    }

    int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

    bool same(int a, int b) { return find(a) == find(b); }

    void join(int a, int b) {
        int fa = find(a), fb = find(b);
        h[fa] = fb;
    }
} ufs1, ufs2;

int kruscal() {
    sort(edge.begin(), edge.end());
    int res = 0;
    for (int i = 0; i < edge.size(); i++) {
        if (ufs2.same(edge[i].u, edge[i].v)) { continue; }
        res += edge[i].w;
        ufs2.join(edge[i].u, edge[i].v);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    ufs1.init(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        ans += abs(u - v);
        ufs1.join(u, v);
    }
    for (int i = 1; i <= n; i++) {
        degree[i]++;
        degree[s]++;
        int lastJ = -1;
        int sum   = 0;
        ufs2.init(n);
        edge.resize(0);
        for (int j = 1; j <= n; j++) {
            if (degree[j] % 2 == 0) { continue; }
            if (lastJ == -1) {
                lastJ = j;
                continue;
            }
            sum += j - lastJ;
            for (int k = lastJ; k < j; k++) { ufs2.join(ufs1.find(k), ufs1.find(k + 1)); }
            lastJ = -1;
        }
        for (int j = 1; j <= n; j++) {
            if (degree[j] == 0) { continue; }
            if (lastJ == -1) {
                lastJ = j;
                continue;
            }
            edge.push_back({ufs1.find(j), ufs1.find(lastJ), j - lastJ});
            lastJ = j;
        }
        cout << ans + sum + kruscal() * 2 << " ";
        degree[i]--;
        degree[s]--;
    }
    cout << endl;
    return 0;
}
