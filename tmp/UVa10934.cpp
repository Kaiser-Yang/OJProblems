#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int k;
    unsigned long long n;
    vector<vector<unsigned long long>> dp;
    dp.resize(101);
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(64);
    }
    dp[0][0] = 0;
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 63; j++) {
            dp[i][j] = dp[i - 1][j - 1] + 1 + dp[i][j - 1];
        }
    }
    while (cin >> k >> n && k != 0 && n != 0) {
        bool ok = false;
        for (int j = 1; j <= 63; j++) {
            if (dp[k][j] >= n) {
                cout << j << endl;
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << "More than 63 trials needed.\n";
        }
    }
    return 0;
}