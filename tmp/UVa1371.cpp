#include <bits/stdc++.h>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

int T, n, m, L, R, mid, ans;
string a, b;
vector<vector<int>> dp(5001, vector<int>(51));

bool check(int res) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) { dp[i][j] = INF; }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) { dp[i][0] = i; }
    for (int j = 1; j <= m; j++) { dp[0][j] = j; }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (a[i] == b[j] ? 0 : 1));  // change
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);  // delete a[i] or insert a[i] at j+1 of b
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);  // delete a[j] or insert b[j] at i+1 of a
        }
        if (dp[i][m] <= res) { dp[i][0] = 0; }
    }
    return dp[n][m] <= res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> b >> a;
        n = a.length(), m = b.length();
        a = " " + a;
        b = " " + b;
        L = 0, R = m, ans = -1;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (check(mid)) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
