// problem statement: https://codeforces.com/problemset/problem/2028/C

#include <bits/stdc++.h>

using namespace std;

int T, n, m, v;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> v;
        vector<long long> a(n + 1), sum(n + 1);
        for (int i = 1; i <= n; i++) { cin >> a[i]; sum[i] = sum[i - 1] + a[i]; }
        vector<int> cnt1(n + 1), cnt2(n + 1);
        int las = 0;
        for (int i = 1; i <= n; i++) {
            cnt1[i] = cnt1[las] + (sum[i] - sum[las] >= v);
            cnt1[i] = max(cnt1[i], cnt1[i - 1]);
            if (cnt1[i] > cnt1[las]) {
                las = i;
            }
        }
        if (cnt1[n] < m) {
            cout << "-1\n";
            continue;
        }
        las = n + 1;
        for (int i = n; i >= 1; i--) {
            cnt2[i] = (las == n + 1 ? 0 : cnt2[las]) + (sum[las - 1] - sum[i - 1] >= v);
            cnt2[i] = max(cnt2[i], (i + 1 > n ? 0 : cnt2[i + 1]));
            if ((las == n + 1 && cnt2[i] > 0) || (las != n + 1 && cnt2[i] > cnt2[las])) {
                las = i;
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt1[i - 1] >= m) {
                ans = max(ans, sum[n] - sum[i - 1]);
                continue;
            }
            auto p = lower_bound(cnt2.rbegin(), cnt2.rend() - 1, m - cnt1[i - 1]) - cnt2.rbegin();
            p = n - p;
            ans = max(ans, sum[p - 1] - sum[i - 1]);
        }
        cout << ans << endl;
    }
    return 0;
}
