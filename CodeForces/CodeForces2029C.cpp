// problem statement: https://codeforces.com/problemset/problem/2029/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
string a, b;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> a(n);
        vector<vector<int>> dp(n, vector<int>(3));
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        dp[0][0] = (a[0] > 0);
        dp[0][1] = 0;
        dp[0][2] = 0;
        int maxDpI0 = dp[0][0];
        for (int i = 1; i < n; i++) {
            if (a[i] > dp[i - 1][0]) {
                dp[i][0] = dp[i - 1][0] + 1;
            } else if (a[i] == dp[i - 1][0]) {
                dp[i][0] = dp[i - 1][0];
            } else {
                dp[i][0] = dp[i - 1][0] - 1;
            }
            dp[i][1] = maxDpI0;
            if (a[i] > dp[i - 1][2]) {
                dp[i][2] = dp[i - 1][2] + 1;
            } else if (a[i] == dp[i - 1][2]) {
                dp[i][2] = dp[i - 1][2];
            } else {
                dp[i][2] = dp[i - 1][2] - 1;
            }
            dp[i][2] = max(dp[i][2], dp[i][1]);
            maxDpI0 = max(maxDpI0, dp[i][0]);
        }
        cout << dp[n - 1][2] << '\n';
    }
    return 0;
}
