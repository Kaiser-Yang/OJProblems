#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int m, n;
    string str;
    vector<vector<int>> dp, cnt;
    while (cin >> m >> n && n != 0 && m != 0) {
        dp.clear();
        dp.resize(1 << m);
        for (int i = 0; i < (1 << m); i++) {
            dp[i].resize(1 << m, -1);
        }
        cnt.clear();
        cnt.resize(1 << m);
        for (int i = 0; i < (1 << m); i++) {
            cnt[i].resize(1 << m, 0);
        }
        for (int i = 0; i < n; i++) {
            cin >> str;
            int status = 0;
            for (int j = 0; j < m; j++) {
                if (str[j] == '1') {
                    status |= 1 << j;
                }
            }
            for (int s = 0; s < (1 << m); s++) {
                cnt[s][status & s]++;
            }
        }
        for (int s = (1 << m) - 1; s >= 0; s--) {
            for (int ss = s; ; ss = (ss - 1) & s) {
                if (cnt[s][ss] == 1) { dp[s][ss] = 0; }
                if (dp[s][ss] != -1) {
                    if (ss == 0) {
                        break;
                    } else {
                        continue;
                    }
                }
                dp[s][ss] = m;
                for (int k = 0; k < m; k++) {
                    if ((1 << k) & s) { continue; }
                    dp[s][ss] = min(dp[s][ss], max(dp[s | (1 << k)][ss | (1 << k)], dp[s | (1 << k)][ss]) + 1);
                }
                if (ss == 0) { break; }
            }
        }
        cout << dp[0][0] << endl;
    }
    return 0;
}