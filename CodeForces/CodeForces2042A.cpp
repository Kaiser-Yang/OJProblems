// problem statement: https://codeforces.com/contest/2042/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, k, n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        sort(a.rbegin(), a.rend());
        int now = 0, ans = -1;
        for (int i = 0; i < n; i++) {
            now += a[i];
            if (now < k) {
                continue;
            } else if (now == k) {
                ans = 0;
                break;
            } else {
                now -= a[i];
                ans = k - now;
                break;
            }
        }
        if (now < k) { ans = k - now; }
        cout << ans << '\n';
    }
    return 0;
}
