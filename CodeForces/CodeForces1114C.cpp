// problem statement: https://codeforces.com/contest/1114/problem/C

#include <bits/stdc++.h>

using namespace std;

long long n, b;

map<long long, int> prime_factorization(long long x) {
    map<long long, int> res;
    for (long long i = 2; i * i <= x; i++) {
        int cnt = 0;
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
                cnt++;
            }
        }
        if (cnt > 0) { res[i] = cnt; }
    }
    if (x > 1) { res[x] = 1; }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> b;
    long long ans = numeric_limits<long long>::max();
    auto b_prime_factor = prime_factorization(b);
    for (auto &&[p, cnt1] : b_prime_factor) {
        long long tmp_n = n, cnt2 = 0;
        while (tmp_n > 0) {
            cnt2 += tmp_n / p;
            tmp_n /= p;
        }
        ans = min(ans, 1LL * cnt2 / cnt1);
    }
    cout << ans << endl;
    return 0;
}
