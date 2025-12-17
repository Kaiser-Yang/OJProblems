#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    vector<vector<int>> mp, dp, path;
    while (cin >> n >> m) {
        mp.resize(n);
        dp.clear();
        dp.resize(n);
        path.resize(n);
        for (int i = 0; i < n; i++) {
            mp[i].resize(m);
            dp[i].resize(m, numeric_limits<int>::max() / 2);
            path[i].resize(m);
            for (int j = 0; j < m; j++) { cin >> mp[i][j]; }
        }
        int first = -1;
        int ans = numeric_limits<int>::max();
        for (int j = m - 1; j >= 0; j--) {
            for (int i = 0; i < n; i++) {
                if (j == m - 1) {
                    dp[i][j] = mp[i][j];
                } else {
                    vector<int> row;
                    row.push_back(i);
                    row.push_back(i + 1);
                    row.push_back(i - 1);
                    if (i == 0) { row[2] = n - 1; }
                    if (i == n - 1) { row[1] = 0; }
                    sort(row.begin(), row.end());
                    for (int k = 0; k < row.size(); k++) {
                        if (dp[row[k]][j + 1] + mp[i][j] < dp[i][j]) {
                            dp[i][j] = dp[row[k]][j + 1] + mp[i][j];
                            path[i][j] = row[k];
                        }
                    }
                }
                if (j == 0 && dp[i][j] < ans) {
                    ans = dp[i][j];
                    first = i;
                }
            }
        }
        cout << first + 1;
        for (int i = path[first][0], j = 1; j < m; i = path[i][j], j++) {
            cout << " " << i + 1;
        }
        cout << endl << ans << endl;
    }
    return 0;
}
