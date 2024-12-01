// problem statement: https://codeforces.com/contest/1187/problem/C

#include <bits/stdc++.h>

using namespace std;

struct Limit {
    int type, l, r;
    bool operator<(const Limit &other) const { return type > other.type; }
};

int n, m;
vector<Limit> limit;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    limit.resize(m);
    for (int i = 0; i < m; i++) { cin >> limit[i].type >> limit[i].l >> limit[i].r; }
    sort(limit.begin(), limit.end());
    vector<int> ans(n, -1);
    ans[0] = n;
    for (int i = 0; i < m; i++) {
        if (limit[i].type == 0) { break; }
        for (int j = limit[i].l; j <= limit[i].r - 1; j++) { ans[j] = 0; }
    }
    for (int i = m - 1; i >= 0; i--) {
        if (limit[i].type == 1) { break; }
        bool fail = true;
        for (int j = limit[i].l; j <= limit[i].r - 1; j++) {
            if (ans[j] == -1) {
                fail = false;
                break;
            }
        }
        if (fail) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "Yes\n";
    cout << ans[0];
    for (int i = 1; i < n; i++) {
        ans[i] += ans[i - 1];
        cout << " " << ans[i];
    }
    cout << "\n";
    return 0;
}
