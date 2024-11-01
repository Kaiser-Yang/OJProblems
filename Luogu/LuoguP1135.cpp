// problem statement: https://www.luogu.com.cn/problem/P1135
// Tag: having been in my blog

#include <bits/stdc++.h>

constexpr int MAXN = 210;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n, a, b, p;
int dp[MAXN][MAXN];

int main() {
    cin >> n >> a >> b;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) { dp[i][i] = 0; }
    for (int i = 1; i <= n; i++) {
        cin >> p;
        if (i - p >= 1) { dp[i][i - p] = 1; }
        if (i + p <= n) { dp[i][i + p] = 1; }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) { dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]); }
        }
    }
    cout << (dp[a][b] == INF ? -1 : dp[a][b]) << endl;
    return 0;
}
