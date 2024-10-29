// problem statemen: https://csacademy.com/ieeextreme-practice/task/invertible-pairs

#include <bits/stdc++.h>

using namespace std;

int T, n;
long long a[200000 + 10];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) { cin >> a[i]; }
        vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + a[i];
                dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) - a[i];
            } else {
                dp[i][0] = dp[i - 1][0] + a[i];
                dp[i][1] = dp[i - 1][1] - a[i];
            }
            dp[i][0] = max(dp[i][0], a[i]);
            dp[i][1] = max(dp[i][1], -a[i]);
            ans = max({ans, dp[i][0], dp[i][1]});
        }
        cout << ans << endl;
    }
    return 0;
}
