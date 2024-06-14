// problem statement: https://www.luogu.com.cn/problem/P1195
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e3 + 10;
constexpr int MAXM = 1e4 + 10;

int n, m, k;
int h[MAXN];

struct Edge
{
    int u, v, w;
} edge[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b)
{
    int fa = find(a);
    int fb = find(b);
    h[fa] = fb;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m, [] (const auto &a, const auto &b) { return a. w < b.w; });
    for (int i = 1; i <= n; i++) { h[i] = i; }
    int cnt = 0, ans = 0;
    for (int i = 0; i < m; i++) {
        if (!same(edge[i].u, edge[i].v)) {
            join(edge[i].u, edge[i].v);
            ans += edge[i].w;
            cnt++;
        }
        if (cnt == n -  k) { break; }
    }
    if (cnt == n - k) { cout << ans << endl; }
    else { cout << "No Answer" << endl; }
	return 0;
}
