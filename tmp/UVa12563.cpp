#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, n, t;
    vector<vector<int>> dp, time;
    vector<int> len;
    cin >> T;
    for (int kase = 1; kase <= T; kase++) {
        cin >> n >> t;
        len.resize(n);
        int tot = 0;
        for (int i = 0; i < n; i++) {
            cin >> len[i];
            tot += len[i];
        }
        dp.clear();
        time.clear();
        dp.resize(n + 1);
        time.resize(n + 1);
        tot = min(tot, t);
        for (int i = 0; i <= n; i++) {
            dp[i].resize(tot + 1);
            time[i].resize(tot + 1);
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int c = 0; c < dp[i].size(); c++) {
                dp[i][c] = dp[i + 1][c];
                time[i][c] = time[i + 1][c];
                if (c >= len[i]) {
                    if (dp[i + 1][c - len[i]] + 1 > dp[i][c]) {
                        dp[i][c] = dp[i + 1][c - len[i]] + 1;
                        time[i][c] = time[i + 1][c - len[i]] + len[i];
                    } else if (dp[i + 1][c - len[i]] + 1 == dp[i][c]) {
                        time[i][c] = max(time[i][c], time[i + 1][c - len[i]] + len[i]);
                    }
                }
            }
        }
        int ans1 = dp[0][tot], ans2 = time[0][tot];
        if (ans2 == t) {
            ans1 = dp[0][t - 1];
            ans2 = time[0][t - 1];
        }
        ans1++;
        ans2 += 678;
        cout << "Case " << kase << ": " << ans1 << " " << ans2 << endl;
    }
    return 0;
}
