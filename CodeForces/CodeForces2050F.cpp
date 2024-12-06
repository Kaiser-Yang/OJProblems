// problem statement: https://codeforces.com/problemset/problem/2050/F

#include <bits/stdc++.h>

using namespace std;

int T, n, q;
vector<int> a;
vector<vector<int> > dp;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> q;
        a.resize(n + 1);
        dp.resize(n + 1, vector<int>(20, 0));
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i][0] = abs(a[i] - a[i - 1]);
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                dp[i][j] = gcd(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            if (l == r) {
                cout << "0" << " \n"[q == 0];
                continue;
            }
            l++;
            int k = log2(r - l + 1);
            cout << gcd(dp[l][k], dp[r - (1 << k) + 1][k]) << " \n"[q == 0];
        }
    }
    return 0;
}
