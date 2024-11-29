// problem statement: https://codeforces.com/contest/2035/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int T, n;
vector<pair<int, int>> pos;

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
    cin >> T;
    while (T--) {
        cin >> n;
        pos.clear();
        long long sum = 0, a;
        for (int i = 1; i <= n; i++) {
            cin >> a;
            int cnt = 0;
            while (a % 2 == 0) {
                a /= 2;
                cnt++;
            }
            while (!pos.empty()) {
                if (cnt >= 30 || pos.back().first <= (a << cnt)) {
                    cnt += pos.back().second;
                    sum += pos.back().first;
                    pos.pop_back();
                } else {
                    break;
                }
            }
            if (cnt > 0) { pos.emplace_back(a, cnt); }
            else {  sum += a; }
            long long ans = sum;
            for (auto [x, y] : pos) {
                ans += x * quick_pow(2, y, MOD) % MOD;
            }
            cout << ans % MOD << " \n"[i == n];
        }
    }
    return 0;
}
