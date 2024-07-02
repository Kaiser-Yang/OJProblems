#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 11;
constexpr int MAXM = 11;

int n, m, cnt;
long long dp[MAXM + 1][1 << MAXN];
bool valid;
vector<int> status[1 << MAXN];

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        if (n == 0 && m == 0) { break; }
        for (int s = 0; s < (1 << n); s++) {
            status[s].clear();
            for (int ns = 0; ns < (1 << n); ns++) {
                valid = true;
                cnt   = 0;
                for (int j = 0; j < n; j++) {
                    if (((1 << j) & s) && ((1 << j) & ns)) {
                        valid = false;
                        break;
                    }
                    if (!((1 << j) & s) && !((1 << j) & ns)) {
                        cnt++;
                    } else if (cnt & 1) {
                        valid = false;
                        break;
                    }
                }
                if (cnt & 1) { valid = false; }
                if (valid) { status[s].push_back(ns); }
            }
        }
        for (int i = 0; i < m; i++) { memset(dp + i, 0, sizeof(long long) * (1 << n)); }
        dp[m][0] = 0;
        dp[0][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int s = 0; s < (1 << n); s++) {
                for (int ns : status[s]) { dp[i + 1][ns] += dp[i][s]; }
            }
        }
        cout << dp[m][0] << endl;
    }
    return 0;
}
