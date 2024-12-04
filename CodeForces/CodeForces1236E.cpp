// problem satement: https://codeforces.com/problemset/problem/1236/E

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> a;
map<int, int> l, r;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    a.resize(m + 1);
    for (int i = 1; i <= m; i++) { cin >> a[i]; }
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    for (int i = m; i >= 1; i--) {
        r[a[i] - i] = r[a[i] - i - 1] + 1;
        l[a[i] + i] = l[a[i] + i + 1] + 1;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += min(n, i + m + 1 - r[i]) - max(1, i - (m + 1) + l[i]) + 1;
    }
    cout << ans << '\n';
    return 0;
}
