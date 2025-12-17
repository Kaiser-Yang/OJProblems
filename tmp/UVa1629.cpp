#include <bits/stdc++.h>

using namespace std;

int cherryNum(int x1, int y1, int x2, int y2, vector<vector<int>> &sum) {
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int dp(int i,
       int j,
       int k,
       int l,
       vector<vector<int>> &sum,
       vector<vector<vector<vector<int>>>> &d) {
    static const int INF = numeric_limits<int>::max() / 10;
    int &ans = d[i][j][k][l];
    if (ans != -1) { return ans; }
    if (cherryNum(i, j, k, l, sum) == 0) { return ans = INF; }
    if (cherryNum(i, j, k, l, sum) == 1) { return ans = 0; }
    ans = INF;
    for (int p = i + 1; p <= k; p++) {  // horizontally
        ans = min(ans, dp(i, j, p - 1, l, sum, d) + dp(p, j, k, l, sum, d) + l - j + 1);
    }
    for (int p = j + 1; p <= l; p++) {  // vertically
        ans = min(ans, dp(i, j, k, p - 1, sum, d) + dp(i, p, k, l, sum, d) + k - i + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, K, x, y;
    int kase = 0;
    vector<vector<int>> sum;
    vector<vector<vector<vector<int>>>> d;
    while (cin >> n >> m >> K) {
        sum.clear();
        sum.resize(n + 1);
        for (int i = 0; i <= n; i++) { sum[i].resize(m + 1, 0); }
        for (int i = 0; i < K; i++) {
            cin >> x >> y;
            sum[x][y] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
        d.clear();
        d.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            d[i].resize(m + 1);
            for (int j = 0; j <= m; j++) {
                d[i][j].resize(n + 1);
                for (int k = 0; k <= n; k++) { d[i][j][k].resize(m + 1, -1); }
            }
        }
        kase++;
        cout << "Case " << kase << ": " << dp(1, 1, n, m, sum, d) << endl;
    }
    return 0;
}