// problem statement: https://codeforces.com/contest/2050/problem/E

#include <bits/stdc++.h>

using namespace std;

int T;
string a, b, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        vector<vector<int>> dp(a.size() + 1,
                               vector<int>(b.size() + 1, numeric_limits<int>::max() / 2));
        dp[0][0] = 0;
        for (int j = 0; j < b.size(); j++) { dp[0][j + 1] = dp[0][j] + (b[j] != c[j]); }
        for (int i = 0; i < a.size(); i++) { dp[i + 1][0] = dp[i][0] + (a[i] != c[i]); }
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j + 1] + (a[i] != c[i + j + 1]));
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i + 1][j] + (b[j] != c[i + j + 1]));
            }
        }
        cout << dp[a.size()][b.size()] << endl;
    }
    return 0;
}
