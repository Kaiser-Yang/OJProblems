// problem statement: https://www.luogu.com.cn/problem/B3612

#include <bits/stdc++.h>

using namespace std;

int n, m, l, r;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        cout << a[r] - a[l - 1] << "\n";
    }
    return 0;
}
