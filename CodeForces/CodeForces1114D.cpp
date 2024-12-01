// problem statement: https://codeforces.com/contest/1114/problem/D

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

int main() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, numeric_limits<int>::max() / 2));
    for (int i = 0; i <= n; i++) { dp[i][i] = 0; }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = min({dp[l][r], dp[l + 1][r] + (a[l] != a[l + 1]), dp[l][r - 1] + (a[r] != a[r - 1])});
            if (a[l] == a[r]) { dp[l][r] = min(dp[l][r], dp[l + 1][r - 1] + 1); }
        }
    }
    cout << dp[1][n] << '\n';
    return 0;
}
