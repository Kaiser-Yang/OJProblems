// problem statement: https://codeforces.com/contest/2050/problem/C

#include <bits/stdc++.h>

using namespace std;

int T;
string s;

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s;
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(9));
        dp[0][0] = true;
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < 9; j++) {
                if (dp[i][j]) {
                    dp[i + 1][(j * 10 + s[i] - '0') % 9] = true;
                    if (s[i] <= '3') {
                        dp[i + 1][(j * 10 + (s[i] - '0') * (s[i] - '0')) % 9] = true;
                    }
                }
            }
        }
        cout << (dp[s.size()][0] ? "YES\n" : "NO\n");
    }
    return 0;
}
