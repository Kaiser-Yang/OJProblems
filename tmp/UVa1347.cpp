#include <bits/stdc++.h>

using namespace std;

double dis(const pair<int, int> &p1, const pair<int, int> &p2) {
    return sqrt((p2.first - p1.first) * (p2.first - p1.first) +
                (p2.second - p1.second) * (p2.second - p1.second));
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<pair<int, int>> p;
    vector<vector<double>> dp;

    while (cin >> n) {
        p.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i].first >> p[i].second; }
        dp.clear();
        dp.resize(n);
        for (int i = 0; i < n; i++) { dp[i].resize(n, numeric_limits<double>::max() / 2); }
        for (int j = 0; j < n - 1; j++) { dp[n - 1][j] = dis(p[j], p[n - 1]); }
        for (int i = n - 2; i >= 1; i--) {
            for (int j = 0; j < i; j++) {
                dp[i][j] =
                    min(dp[i + 1][j] + dis(p[i], p[i + 1]), dp[i + 1][i] + dis(p[j], p[i + 1]));
            }
        }
        cout << fixed << setprecision(2) << dp[1][0] + dis(p[0], p[1]) << endl;
    }
    return 0;
}
