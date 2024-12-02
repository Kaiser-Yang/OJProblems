// problem statement: https://codeforces.com/contest/2042/problem/D

#include <bits/stdc++.h>

using namespace std;

int T, n;
struct State {
    int l, r, i;
};
vector<State> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].l >> a[i].r;
            a[i].i = i;
        }
        sort(a.begin(), a.end(), [](const auto &x, const auto &y) {
            if (x.l != y.l) { return x.l < y.l; }
            return x.r > y.r;
        });
        vector<int> ans(n);
        set<int> occur;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
            } else {
                if (i + 1 < n && a[i + 1].l == a[i].l && a[i + 1].r == a[i].r) {
                } else if (a[i].l == a[i - 1].l && a[i].r == a[i - 1].r) {
                } else {
                    auto p = occur.lower_bound(a[i].r);
                    if (p != occur.end()) { ans[a[i].i] = *p - a[i].r; }
                }
            }
            occur.insert(a[i].r);
        }
        sort(a.begin(), a.end(), [](const auto &x, const auto &y) {
            if (x.r != y.r) { return x.r > y.r; }
            return x.l < y.l;
        });
        occur.clear();
        for (int i = 0; i < n; i++) {
            if (i == 0) {
            } else {
                if (i + 1 < n && a[i + 1].l == a[i].l && a[i + 1].r == a[i].r) {
                } else if (a[i].l == a[i - 1].l && a[i].r == a[i - 1].r) {
                } else {
                    auto p = occur.upper_bound(a[i].l);
                    if (p != occur.begin()) {
                        p--;
                        ans[a[i].i] += a[i].l - *p;
                    }
                }
            }
            occur.insert(a[i].l);
        }
        for (int i = 0; i < n; i++) { cout << ans[i] << "\n"; }
    }
    return 0;
}
