// problem statement: https://csacademy.com/ieeextreme-practice/task/halving

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 310;
constexpr int MOD = 998244353;

int n;

enum { MIN, MAX };

struct {
    int a1, a2, r, b;
} record[MAXN];

set<int> sure;
map<int, int> b_to_r;

long long ans = 1;
int dp[2][MAXN][MAXN];

void check_zero_res() {
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cnt[record[i].a1]++;
        cnt[record[i].a2]++;
        if (record[i].a1 != -1 && record[i].a2 != -1 &&
            ((record[i].r == MIN && min(record[i].a1, record[i].a2) != record[i].b) ||
             (record[i].r == MAX && max(record[i].a1, record[i].a2) != record[i].b))) {
            cout << "0\n";
            exit(0);
        }
    }
    cnt.erase(-1);
    for (auto &p : cnt) {
        if (p.second > 1) {
            cout << "0\n";
            exit(0);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            cin >> record[i / 2].a1;
        } else {
            cin >> record[i / 2].a2;
        }
    }
    for (int i = 0; i < n; i++) { cin >> record[i].r; }
    for (int i = 0; i < n; i++) {
        cin >> record[i].b;
        b_to_r[record[i].b] = record[i].r;
    }
    for (int i = 0; i < n; i++) {
        if (record[i].a1 != -1 && record[i].a2 != -1) {
            sure.insert(record[i].a1);
            sure.insert(record[i].a2);
        } else if (record[i].a1 == -1 && record[i].a2 == -1) {
            ans = ans * 2LL % MOD;
        } else {
            if (record[i].a1 == -1) {
                if (record[i].a2 != record[i].b) {
                    record[i].a1 = record[i].b;
                    sure.insert(record[i].a1);
                    sure.insert(record[i].a2);
                }
            } else if (record[i].a2 == -1) {
                if (record[i].a1 != record[i].b) {
                    record[i].a2 = record[i].b;
                    sure.insert(record[i].a1);
                    sure.insert(record[i].a2);
                }
            } else {
                return -1;
            }
        }
    }
    check_zero_res();
    int now = 1, las = 0;
    dp[0][0][0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 0; j <= min(i, n); j++) {
            for (int k = 0; k + j <= i && k <= n; k++) {
                if (sure.count(i)) {
                    dp[now][j][k] = dp[las][j][k];
                } else if (b_to_r.count(i)) {
                    if (b_to_r[i] == MAX) {
                        dp[now][j][k] = 1LL * dp[las][j][k + 1] * (k + 1) % MOD;
                    } else {
                        if (j == 0) {
                            dp[now][j][k] = 0;
                        } else {
                            dp[now][j][k] = dp[las][j - 1][k];
                        }
                    }
                } else {
                    if (k == 0) {
                        dp[now][j][k] = 0;
                    } else {
                        dp[now][j][k] = dp[las][j][k - 1];
                    }
                    dp[now][j][k] += 1LL * dp[las][j + 1][k] * (j + 1) % MOD;
                    dp[now][j][k] %= MOD;
                }
            }
        }
        swap(now, las);
    }
    cout << 1LL * ans * dp[las][0][0] % MOD << endl;
    return 0;
}
