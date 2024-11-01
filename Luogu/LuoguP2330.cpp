// problem statement: https://www.luogu.com.cn/problem/P2330
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 310;
constexpr int MAXM = 8010;

int n, m, cnt, ans;
int h[MAXN];

struct edge {
    int u, v, w;
} edge[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    h[fa] = fb;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [](const auto &a, const auto &b) { return a.w < b.w; });
    for (int i = 0; i < m; i++) {
        if (same(edge[i].u, edge[i].v)) { continue; }
        join(edge[i].u, edge[i].v);
        cnt++;
        ans = max(ans, edge[i].w);
        if (cnt == n - 1) { break; }
    }
    cout << cnt << " " << ans << endl;
    return 0;
}
