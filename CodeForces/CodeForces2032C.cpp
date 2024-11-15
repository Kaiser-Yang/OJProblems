// problem statement: https://codeforces.com/contest/2032/problem/C

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int T, n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) { cin >> a[i]; }
        sort(a + 1, a + 1 + n);
        int l = 1, r = 3, ans = n - 2;
        while (r <= n) {
            while (l + 1 < r && a[r] >= a[l] + a[l + 1]) { l++; }
            ans = min(ans, n - (r - l + 1));
            r++;
        }
        cout << ans << '\n';
    }
    return 0;
}
