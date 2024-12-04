// problem statement: https://codeforces.com/problemset/problem/1236/B

#include <bits/stdc++.h>

constexpr int MOD = 1e9 + 7;

using namespace std;

int n, m;

int quick_pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    cin >> n >> m;
    cout << quick_pow((quick_pow(2, m, MOD) - 1 + MOD) % MOD, n, MOD) << endl;
    return 0;
}
