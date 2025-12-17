#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 40001;

int T, n, m, d;
int w[MAXN];
int dp[MAXN][2];

bool check(int res) {
    static constexpr int INF = numeric_limits<int>::max();
    dp[0][0] = 0;
    dp[0][1] = dp[1][0] = dp[1][1] = INF;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i][1] = INF;
        for (int j = 1; j <= d && i - 2 * j >= 0; j++) {
            if (w[i] - w[i - j] > res) { break; }
            if (w[i - j] - w[i - 2 * j] > res) { continue; }
            if (dp[i - 2 * j][1] != INF) { dp[i][0] = min(dp[i][0], dp[i - 2 * j][1] + 1); }
            if (dp[i - 2 * j][0] != INF) { dp[i][1] = min(dp[i][1], dp[i - 2 * j][0] + 1); }
        }
    }
    return dp[n][(m - 1) % 2] < m;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> d;
        for (int i = 1; i <= n; i++) {
            cin >> w[i];
            w[i] += w[i - 1];
        }
        if ((n % 2 == 1) || (n < 2 * (m - 1)) || (n > 2 * d * (m - 1))) {
            cout << "BAD\n";
            continue;
        }
        int left = 0, right = w[n], ans = -1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (check(mid)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
