// problem statement: https://codeforces.com/contest/839/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr int MAX_A = 1e6 + 10;

int n;
long long a, ans, max_a;
vector<long long> dp;
int cnt[MAX_A];

long long quick_pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) { res = res * a % mod; }
        a = a * a % mod;
        b >>= 1;
    }
    return res % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        max_a = max(max_a, a);
        cnt[a]++;
    }
    dp.resize(max_a + 1);
    for (int i = max_a; i > 1; i--) {
        long long cnt_i = 0;
        for (int j = i; j <= max_a; j += i) { cnt_i += cnt[j]; }
        if (cnt_i == 0) { continue; }
        dp[i] = cnt_i * quick_pow(2, cnt_i - 1, MOD) % MOD;
        for (int j = i + i; j <= max_a; j += i) { dp[i] = (dp[i] - dp[j] + MOD) % MOD; }
        ans = (ans + dp[i] * i % MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}
