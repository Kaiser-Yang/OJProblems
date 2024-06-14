// problem statement: https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a

#include <bits/stdc++.h>

using namespace std;

int n, k, ans;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = 1; i + k - 1 <= n; i++) { ans = max(ans, a[i + k - 1] - a[i - 1]); }
    cout << ans << "\n";
    return 0;
}
