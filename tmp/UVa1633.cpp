#include <bits/stdc++.h>

using namespace std;

int T, n, k;
vector<vector<int>> d;
vector<vector<bool>> repeat;
constexpr int MOD = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    repeat.resize(12);
    for (int i = 0; i < 12; i++) {
        repeat[i].resize(1 << i);
    }
    repeat[1][0] = repeat[1][1] = true;
    for (int i = 2; i < 12; i++) {
        for (int j = 0; j < 1 << i; j++) {
            bool ok = true;
            for (int k = 0; k < i / 2; k++) {
                if (((j & (1 << k)) && !(j & (1 << (i - k - 1)))) || (!(j & (1 << k)) && (j & (1 << (i - k - 1))))){
                    ok = false;
                }
            }
            repeat[i][j] = ok;
        }
    }
    while (T--) {
        cin >> n >> k;
        if (k == 1) {
            cout << "0" << endl;
            continue;
        }
        d.clear();
        d.resize(n + 1);
        for (int i = 0; i < n + 1; i++) {
            d[i].resize(1 << min(i, k), 0);
        }
        d[1][0] = d[1][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < (1 << min(i - 1, k)); j++) {
                for (int h = 0; h < 2; h++) {
                    int s = ((j << 1) + h) & ((1 << k) - 1);
                    if ((i >= k && repeat[k][s]) || (i > k && repeat[k + 1][(j << 1) + h])) {
                        continue;
                    }
                    d[i][s] = (d[i][s] + d[i -1][j]) % MOD;
                }
            }
        }
        int ans = 0;
        for (int j = 0; j < (1 << min(n, k)); j++) {
            ans = (ans + d[n][j]) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}
