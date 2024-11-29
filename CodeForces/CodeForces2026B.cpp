// problem statement: https://codeforces.com/contest/2026/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        if (n == 1) {
            cout << "1\n";
            continue;
        }
        long long ans = 0;
        if (n % 2 == 0) {
            for (int i = 0; i + 1 < n; i += 2) { ans = max(ans, a[i + 1] - a[i]); }
        } else {
            ans = numeric_limits<long long>::max();
            for (int i = 0; i < n; i++) {
                long long tmp = 0;
                if (i % 2 == 0) {
                    for (int j = 0; j + 1 < i; j += 2) { tmp = max(tmp, a[j + 1] - a[j]); }
                    for (int j = i + 1; j + 1 < n; j += 2) { tmp = max(tmp, a[j + 1] - a[j]); }
                } else {
                    for (int j = 0; j + 1 < i; j += 2) { tmp = max(tmp, a[j + 1] - a[j]); }
                    for (int j = i - 1; j + 1 < n; j += 2) { tmp = max(tmp, a[j + 1] - a[j]); }
                }
                ans = min(ans, tmp);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
