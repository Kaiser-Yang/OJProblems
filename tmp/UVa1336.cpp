#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, c;
    double d;
    bool operator<(const Node &other) { return x < other.x; }
};

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    int n, v, x;
    vector<Node> repairment;
    vector<vector<vector<double>>> dp;
    vector<double> sum;
    while (cin >> n >> v >> x && n != 0 && v != 0 && x != 0) {
        repairment.clear();
        repairment.emplace_back(Node());
        for (int i = 1; i <= n; i++) {
            int x, c;
            double d;
            cin >> x >> c >> d;
            repairment.emplace_back(Node{x, c, d});
        }
        sort(repairment.begin() + 1, repairment.end());
        sum.clear();
        sum.resize(n + 2);
        for (int i = 1; i <= n; i++) { sum[i] = sum[i - 1] + repairment[i].d; }
        dp.clear();
        dp.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            dp[i].resize(n + 1);
            for (int j = 0; j <= n; j++) { dp[i][j].resize(2); }
        }
        for (int i = n; i >= 1; i--) {
            dp[i][i][0] = dp[i][i][1] = sum[n] * abs(x - repairment[i].x) / v + repairment[i].c;
            for (int j = i + 1; j <= n; j++) {
                dp[i][j][0] =
                    min(dp[i + 1][j][0] + (sum[i] + sum[n] - sum[j]) *
                                              abs(repairment[i + 1].x - repairment[i].x) / v,
                        dp[i + 1][j][1] + (sum[i] + sum[n] - sum[j]) *
                                              abs(repairment[j].x - repairment[i].x) / v) +
                    repairment[i].c;

                dp[i][j][1] =
                    min(dp[i][j - 1][0] + (sum[i - 1] + sum[n] - sum[j - 1]) *
                                              abs(repairment[i].x - repairment[j].x) / v,
                        dp[i][j - 1][1] + (sum[i - 1] + sum[n] - sum[j - 1]) *
                                              abs(repairment[j - 1].x - repairment[j].x) / v) +
                    repairment[j].c;
            }
        }
        cout << (int)min(dp[1][n][0], dp[1][n][1]) << endl;
    }
    return 0;
}