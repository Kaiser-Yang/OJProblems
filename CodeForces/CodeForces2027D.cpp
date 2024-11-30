// problem statement: https://codeforces.com/contest/2027/problem/D2

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int T, n, m;
vector<long long> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        a.resize(n + 1);
        b.resize(m + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += a[i - 1];
        }
        for (int i = 1; i <= m; i++) { cin >> b[i]; }
        vector<vector<long long>> dp(
            n + 1, vector<long long>(m + 1, numeric_limits<long long>::max() / 2)),
            f(n + 1, vector<long long>(m + 1));
        for (int j = 1; j <= m; j++) {
            dp[0][j] = 0;
            f[0][j] = 1;
        }
        for (int j = 1; j <= m; j++) {
            int l = 0, r = l;
            long long sum = f[0][j];
            for (int i = 1; i <= n; i++) {
                while (l < i && a[i] - a[l] > b[j]) {
                    if (l <= r) { sum = (sum - f[l][j] + MOD) % MOD; }
                    l++;
                }
                if (l > r && l < i) {
                    r = l;
                    sum = f[l][j];
                    while (r + 1 < i && dp[r + 1][j] == dp[l][j]) { sum = (sum + f[++r][j]) % MOD; }
                }
                if (l < i && dp[i][j - 1] > dp[l][j] + m - j) {
                    dp[i][j] = dp[l][j] + m - j;
                    f[i][j] = sum % MOD;
                } else if (l < i && dp[i][j - 1] == dp[l][j] + m -j) {
                    dp[i][j] = dp[i][j - 1];
                    f[i][j] = ((i == n ? 0 : f[i][j - 1]) + sum) % MOD;
                } else {
                    if (i == n) { continue; }
                    dp[i][j] = dp[i][j - 1];
                    f[i][j] = f[i][j - 1];
                }
                if (l == i) {
                    r = l;
                    sum = f[i][j];
                } else if (dp[i][j] == dp[r][j]) {
                    sum = (sum + f[i][j]) % MOD;
                    r++;
                }
            }
        }
        long long ans1 = numeric_limits<long long>::max() / 2;
        for (int j = 1; j <= m; j++) { ans1 = min(ans1, dp[n][j]); }
        if (ans1 == numeric_limits<long long>::max() / 2) {
            cout << "-1\n";
        } else {
            long long ans2 = 0;
            for (int j = 1; j <= m; j++) {
                if (dp[n][j] == ans1) { ans2 = (ans2 + f[n][j]) % MOD; }
            }
            cout << ans1 << ' ' << ans2 << '\n';
        }
    }
    return 0;
}
