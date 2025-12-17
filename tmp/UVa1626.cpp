#include <bits/stdc++.h>

using namespace std;

void print(int i, int j, vector<vector<int>> &dp, string &s)
{
    if (i > j) { return; }
    if (i == j) {
        if (s[i] == '(' || s[i] == ')') {
            cout << "()";
        } else {
            cout << "[]";
        }
        return;
    }
    if (((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')) && dp[i][j] == dp[i + 1][j - 1]) {
        cout << s[i]; print(i + 1, j - 1, dp, s); cout << s[j];
        return;
    }
    for (int k = i; k < j; k++) {
        if (dp[i][j] == dp[i][k] + dp[k + 1][j]) {
            print(i, k, dp, s);
            print(k + 1, j, dp, s);
            return;
        }
    }
}

int main()
{
    int T;
    string s;
    vector<vector<int>> dp;
    cin >> T;
    getchar();
    while (T--) {
        getline(cin, s);
        getline(cin, s);
        int n = s.length();
        dp.clear();
        dp.resize(n);
        for (int i = 0; i < n; i++) { dp[i].resize(n); dp[i][i] = 1; }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = 1e9;
                if ((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')) {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        print(0, n - 1, dp, s);
        cout << endl;
        if (T != 0) { cout << endl; }
    }
    return 0;
}
