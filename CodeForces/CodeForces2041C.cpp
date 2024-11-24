// problem statement: https://codeforces.com/contest/2041/problem/C

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 12;

int n, s, t;
int a[MAXN][MAXN][MAXN], dp[1 << MAXN][1 << MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) { cin >> a[i][j][k]; }
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) {
            int cnt_i = __builtin_popcount(i), cnt_j = __builtin_popcount(j);
            if (cnt_i != cnt_j) { continue; }
            for (int x = 0; x < n; x++) {
                if (i & (1 << x)) { continue; }
                for (int y = 0; y < n; y++) {
                    if (j & (1 << y)) { continue; }
                    dp[i | (1 << x)][j | (1 << y)] =
                        min(dp[i | (1 << x)][j | (1 << y)], dp[i][j] + a[x][y][cnt_i]);
                }
            }
        }
    }
    cout << dp[(1 << n) - 1][(1 << n) - 1] << endl;
    return 0;
}
