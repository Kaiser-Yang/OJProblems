// problem statement: https://codeforces.com/contest/2039/problem/C2

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

long long cnt[1000000 + 10];

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> x >> m;
        long long ans = 0;
        int x_bit_cnt = bit_count(x);
        for (int i = 0; i < x; i++) { cnt[i] = 0; }
        for (long long y = 1; y <= min((1LL << x_bit_cnt) - 1, m); y++) {
            cnt[(x ^ y) % x]++;
            if ((x ^ y) % x == 0 || (x ^ y) % y == 0) { ans++; }
        }
        cnt[0]++;
        if ((m >> x_bit_cnt) > 0) {
            long long first_res = -1;
            bool found = false;
            vector<long long> res;
            res.reserve(x + 10);
            for (long long y = (1 << x_bit_cnt); y <= m; y += (1 << x_bit_cnt)) {
                if (first_res == -1) {
                    first_res = y % x;
                } else if (first_res == y % x) {
                    found = true;
                    break;
                }
                res.push_back(y % x);
            }
            if (!found) {
                res.pop_back();
                for (auto &&r : res) { ans += cnt[(x - r) % x]; }
                for (long long y = (1 << x_bit_cnt) + res.size() * (1 << x_bit_cnt); y <= m; y++) {
                    if ((x ^ y) % x == 0 || (x ^ y) % y == 0) { ans++; }
                }
            } else {
                long long tmp_cnt = 0;
                for (auto &&r : res) { tmp_cnt += cnt[(x - r) % x]; }
                ans += tmp_cnt * (((m >> x_bit_cnt) - 1) / res.size());
                int last_part_len = (m >> x_bit_cnt) % res.size();
                if (last_part_len == 0) { last_part_len = res.size(); }
                last_part_len--;
                for (int i = 0; i < last_part_len; i++) { ans += cnt[(x - res[i]) % x]; }
                for (long long y = (m >> x_bit_cnt << x_bit_cnt); y <= m; y++) {
                    if ((x ^ y) % x == 0 || (x ^ y) % y == 0) { ans++; }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
