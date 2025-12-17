#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int L, n;
    vector<int> p;
    vector<vector<int>> dp;
    while (cin >> L && L != 0) {
        cin >> n;
        p.resize(n + 2);
        p[0] = 0;
        p[n + 1] = L;
        for (int i = 1; i <= n; i++) { cin >> p[i]; }
        dp.clear();
        dp.resize(n + 1);
        for (int i = 0; i <= n; i++) { dp[i].resize(n + 1); }
        dp[n][n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j <= n; j++) {
                dp[i][j] = 1e9;
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[j + 1] - p[i]);
                }
            }
        }
        cout << "The minimum cutting is " << dp[0][n] << ".\n";
    }
    return 0;
}
