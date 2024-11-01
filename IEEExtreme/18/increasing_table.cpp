// problem statement: https://csacademy.com/ieeextreme-practice/task/increasing-table

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2000 + 10;
constexpr int MOD = 998244353;

int n, m, x;
set<int> a;
long long dp[2 * MAXN][MAXN][2];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x;
        a.insert(x);
    }
    set<int> s;
    for (int i = 1; i <= 2 * n; i++) { s.insert(i); }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x;
        s.erase(x);
    }
    // val[i].first is the value of the i-th element in the set s
    // val[i].second is true if the i-th element must be chosen
    vector<pair<int, bool>> val;
    for (auto &&ele : s) {
        if (ele == 1 || a.count(ele)) {
            val.push_back({ele, true});
        } else {
            val.push_back({ele, false});
        }
    }
    if (val.size() < n || val[0].first != 1) {
        cout << 0 << endl;
        return 0;
    }
    dp[0][1][1] = 1;
    for (int i = 1; i < val.size(); i++) {
        for (int j = 0; j <= n; j++) {
            if (val[i].second) {
                dp[i][j][0] = 0;
            } else {
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
            }
            if (val[i].first <= 2 * j - 1) {
                dp[i][j][1] = (dp[i - 1][j - 1][1] + dp[i - 1][j - 1][0]) % MOD;
            } else {
                dp[i][j][1] = 0;
            }
        }
    }
    cout << (dp[val.size() - 1][n][1] + dp[val.size() - 1][n][0]) % MOD << endl;
    return 0;
}
