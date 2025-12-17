#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    vector<int> cost({6, 2, 5, 5, 4, 5, 6, 3, 7, 6});
    vector<vector<int>> dp, p;
    int n, m, kase = 0;
    while (cin >> n && n != 0) {
        cin >> m;
        dp.clear();
        dp.resize(n + 1);
        p.clear();
        p.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            dp[i].resize(m, -1);
            p[i].resize(m, -1);
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) { dp[i][j] = 0; }
                for (int d = 9; d >= 0; d--) {
                    if (i - cost[d] < 0) { continue; }
                    if (dp[i - cost[d]][(j * 10 + d) % m] >= 0 && dp[i - cost[d]][(j * 10 + d) % m] + 1 > dp[i][j]){
                        dp[i][j] = dp[i - cost[d]][(j * 10 + d) % m] + 1;
                        p[i][j] = d;
                    }
                }
                cout << i << " " << j << " " << dp[i][j] << " " << p[i][j] << endl;
            }
        }
        kase++;
        cout << "Case " << kase << ": ";
        if (p[n][0] < 0) {
            cout << "-1\n";
        } else {
            int i = n, j = 0;
            bool first = true;
            for (int d = p[i][j]; d >= 0; d = p[i][j]) {
                i -= cost[d];
                j = (j * 10 + d) % m;
                if (first && d == 0 && p[i][j] >= 0) {
                    continue;
                }
                first = false;
                cout << d;
            }
            cout << endl;
        }
    }
    return 0;
}
