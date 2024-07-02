// problem statement: https://www.luogu.com.cn/problem/P1525

#include <bits/stdc++.h>

constexpr size_t MAXN = 2e4 + 10;
constexpr size_t MAXM = 1e6 + 10;

using namespace std;

int n, m;

struct conflict {
    int u, v, w;
    bool operator>(const conflict &rhs) const { return w > rhs.w; }
} conf[MAXM];

template <size_t MAXN>
struct union_find_set {
    int h[MAXN];

    union_find_set() { init(); }

    void init() {
        for (int i = 0; i < MAXN; i++) { h[i] = i; }
    }
    int find(int x) { return h[x] == x ? x : h[x] = find(h[x]); }
    void merge(int x, int y) { h[find(x)] = find(y); }
    bool same(int x, int y) { return find(x) == find(y); }
};

union_find_set<MAXN << 1> ufs;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) { cin >> conf[i].u >> conf[i].v >> conf[i].w; }
    sort(conf, conf + m, greater<conflict>());
    for (int i = 0; i < m; i++) {
        if (!ufs.same(conf[i].u, conf[i].v)) {
            ufs.merge(conf[i].u, conf[i].v + n);
            ufs.merge(conf[i].v, conf[i].u + n);
        } else {
            cout << conf[i].w << '\n';
            return 0;
        }
    }
    cout << "0\n";
    return 0;
}
