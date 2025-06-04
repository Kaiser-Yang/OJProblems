// problem statement: https://www.luogu.com.cn/problem/P2962

#include <bits/stdc++.h>

using namespace std;

int n, m, u, v;
vector<int> a;
map<int, int> f;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) { a[i] = 1 << i; }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--, v--;
        a[u] |= (1LL << v);
        a[v] |= (1LL << u);
    }
    int left_size = n / 2, right_size = n - left_size;
    for (int s = 0; s < 1 << left_size; s++) {
        int status = 0, cnt = 0;
        for (int i = 0; i < left_size; i++) {
            if (s & (1 << i)) {
                status ^= a[i];
                cnt++;
            }
        }
        if (f.count(status)) {
            f[status] = min(f[status], cnt);
        } else {
            f[status] = cnt;
        }
    }
    int ans = numeric_limits<int>::max();
    for (int s = 0; s < 1 << right_size; s++) {
        int status = 0, cnt = 0;
        for (int i = 0; i < right_size; i++) {
            if (s & (1 << i)) {
                status ^= a[left_size + i];
                cnt++;
            }
        }
        int partner_status = ((1LL << n) - 1) ^ status;
        if (f.count(partner_status)) { ans = min(ans, cnt + f[partner_status]); }
    }
    cout << ans << "\n";
    return 0;
}
