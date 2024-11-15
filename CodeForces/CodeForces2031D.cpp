// problem statement: https://codeforces.com/contest/2031/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e5 + 10;

int T, n;
int a[MAXN], pos[MAXN];
int fa[MAXN], minv[MAXN], maxv[MAXN];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) { return; }
    fa[x] = y;
    minv[y] = min(minv[y], minv[x]);
    maxv[y] = max(maxv[y], maxv[x]);
}

int query_min(int x) { return minv[find(x)]; }

int query_max(int x) { return maxv[find(x)]; }

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[i] = i;
        }
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            maxv[i] = minv[i] = a[i];
        }
        sort(pos + 1, pos + 1 + n, [](auto x, auto y) {
            if (a[x] == a[y]) { return x < y; }
            return a[x] < a[y];
        });
        int las = n + 1;
        for (int i = n; i >= 1; i--) {
            if (pos[i] > las) { continue; }
            for (int j = pos[i] + 1; j < las; j++) { join(pos[i], j); }
            if (las != n + 1 && a[pos[i]] > query_min(las)) { join(pos[i], las); }
            las = pos[i];
        }
        for (int i = 1; i <= n; i++) { cout << query_max(i) << (i == n ? '\n' : ' '); }
    }
    return 0;
}
