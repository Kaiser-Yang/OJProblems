// problem statement: https://codeforces.com/problemset/problem/2037/G

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr int MAXA = 1e6 + 5;
constexpr int MOD = 998244353;

int n, ans;
int a[MAXN], dp[MAXA];
vector<int> prime, smallest_prime_factor;
vector<bool> not_prime;

void get_prime_factors(int x, vector<int> &prime_factor) {
    prime_factor.clear();
    while (x > 1) {
        prime_factor.push_back(smallest_prime_factor[x]);
        int tmp = smallest_prime_factor[x];
        while (x % tmp == 0) { x /= tmp; }
    }
}

void get_divisor(int x, vector<int> &divisor) {
    divisor.clear();
    vector<int> prime_factor;
    get_prime_factors(x, prime_factor);
    for (int s = 0; s < (1 << prime_factor.size()); s++) {
        int y = 1;
        bool flag = true;
        for (int i = 0; i < prime_factor.size(); i++) {
            if (s & (1 << i)) {
                y *= prime_factor[i];
                flag = !flag;
            }
        }
        if (y == 1) { continue; }
        if (flag) {
            divisor.push_back(-y);
        } else {
            divisor.push_back(y);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    int max_val = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }
    not_prime.resize(max_val + 1);
    not_prime[0] = not_prime[1] = true;
    smallest_prime_factor.resize(max_val + 1);
    smallest_prime_factor[1] = 1;
    for (int i = 2; i <= max_val; i++) {
        if (!not_prime[i]) {
            smallest_prime_factor[i] = i;
            prime.push_back(i);
        }
        for (int p : prime) {
            if (i * p > max_val) { break; }
            not_prime[i * p] = true;
            smallest_prime_factor[i * p] = p;
            if (i % p == 0) { break; }
        }
    }
    vector<int> divisor;
    for (int i = 1; i <= n; i++) {
        get_divisor(a[i], divisor);
        if (i == 1) {
            for (int d : divisor) { dp[abs(d)] = 1; }
            continue;
        }
        ans = 0;
        for (int d : divisor) {
            if (d > 0) {
                ans = (ans + dp[d]) % MOD;
            } else {
                ans = (ans - dp[-d] + MOD) % MOD;
            }
        }
        for (int d : divisor) { dp[abs(d)] = (dp[abs(d)] + ans) % MOD; }
    }
    cout << ans << '\n';
    return 0;
}
