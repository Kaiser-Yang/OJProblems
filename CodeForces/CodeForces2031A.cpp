// problem statement: https://codeforces.com/contest/2031/problem/A

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 50 + 10;

int T, n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) { cin >> a[i]; }
        int ans = n - 1;
        for (int i = 1; i <= n; i++) {
            int cnt = 0;
            for (int j = 1; j <= n; j++) {
                if (a[j] != a[i]) { cnt++; }
            }
            ans = min(ans, cnt);
        }
        cout << ans << '\n';
    }
    return 0;
}
