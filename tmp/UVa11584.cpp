#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T;
    string s;
    vector<vector<bool>> palindrome;
    vector<int> dp;
    cin >> T;
    while (T--) {
        cin >> s;
        int n = s.length();
        palindrome.clear();
        palindrome.resize(n);
        for (int i = 0; i < n; i++) {
            palindrome[i].resize(n);
            palindrome[i][i] = true;
        }
        for (int i = 0; i < n; i++) {
            int j = 1;
            while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) {
                palindrome[i - j][i + j] = true;
                j++;
            }
            j = 1;
            while (i - j >= 0 && i + j - 1 < n && s[i - j] == s[i + j - 1]) {
                palindrome[i - j][i + j - 1] = true;
                j++;
            }
        }
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            if (palindrome[0][i]) { dp[i] = 1; continue; }
            dp[i] = i + 1;
            for (int j = 0; j < i; j++) {
                if (palindrome[j + 1][i]) { dp[i] = min(dp[i], dp[j] + 1); }
            }
        }
        cout << dp[n - 1] << endl;
    }
    return 0;
}
