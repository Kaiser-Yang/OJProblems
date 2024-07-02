#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 310;

int n, las, now;
int number[MAXN], cost[MAXN];
unordered_map<int, int> dp[2];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> number[i]; }
    for (int i = 1; i <= n; i++) { cin >> cost[i]; }
    now = 0, las = 1;
    dp[las][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[now].clear();
        dp[now][0] = 0;
        for (auto item : dp[las]) {
            int j = item.first;
            if (dp[now].count(j) == 0) {
                dp[now][j] = item.second;
            } else {
                dp[now][j] = min(dp[now][j], item.second);
            }
            int newJ = gcd(j, number[i]);
            if (dp[now].count(newJ) == 0) {
                dp[now][newJ] = item.second + cost[i];
            } else {
                dp[now][newJ] = min(dp[now][newJ], item.second + cost[i]);
            }
        }
        swap(now, las);
    }
    if (dp[las].count(1) == 0) {
        cout << "-1" << endl;
    } else {
        cout << dp[las][1] << endl;
    }
    return 0;
}
