// problem statement: http://poj.org/problem?id=2395
// Tag: having been in my blog

#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

const int MAXN = 2010;
const int MAXM = 1e4 + 10;

int n, m, cnt, ans;
int h[MAXN];

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) { return w < other.w; }
} edge[MAXM];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b) {
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { h[i] = i; }
    for (int i = 0; i < m; i++) { cin >> edge[i].u >> edge[i].v >> edge[i].w; }
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) {
        if (same(edge[i].u, edge[i].v)) { continue; }
        join(edge[i].u, edge[i].v);
        cnt++;
        if (cnt == n - 1) {
            ans = edge[i].w;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
