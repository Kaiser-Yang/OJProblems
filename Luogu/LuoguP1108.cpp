// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e3 + 10;

int N, ans1;
long long ans2;
int a[MAXN], dp[MAXN];
long long num[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++) { cin >> a[i]; }
    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] > a[i]) { dp[i] = max(dp[i], dp[j] + 1); }
        }
        ans1 = max(ans1, dp[i]);
    }
    for (int i = 1; i <= N; i++) {
        if (dp[i] == 1) { num[i] = 1; }
        for (int j = 1; j < i; j++) {
            if (a[i] < a[j] && dp[i] == dp[j] + 1) {
                num[i] += num[j];
            } else if (a[i] == a[j] && dp[i] == dp[j]) {
                num[i] = 0;
            }
        }
        if (dp[i] == ans1) { ans2 += num[i]; }
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
