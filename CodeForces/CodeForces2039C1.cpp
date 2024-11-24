// problem statement: https://codeforces.com/contest/2039/problem/C1

#include <bits/stdc++.h>

using namespace std;

int T;
long long x, m;

int bit_count(long long n) {
    int cnt = 0;
    while (n) {
        n >>= 1;
        cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> x >> m;
        long long ans = 0;
        int x_bit_cnt = bit_count(x);
        for (long long y = 1; y <= min((1LL << x_bit_cnt) - 1, m); y++) {
            if (y == x) { continue; }
            if (x % (x ^ y) == 0 || y % (x ^ y) == 0) {
                ans++;
            }
        }
        if ((m >> x_bit_cnt) > 0) {
            long long tmp = (m >> x_bit_cnt);
            for (long long y = (tmp << x_bit_cnt); y <= m; y++) {
                if (x == y) { continue; }
                if (x % (x ^ y) == 0 || y % (x ^ y) == 0) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
