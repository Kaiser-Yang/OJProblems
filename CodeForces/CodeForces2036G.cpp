// problem statement: https://codeforces.com/contest/2036/problem/G

#include <bits/stdc++.h>

using namespace std;

int T;
long long n, a, b, c;

long long query(long long l, long long r) {
    if (r > n) { r = n; }
    if (l > r) { return 0; }
    cout << "xor " << l << " " << r << '\n';
    cout.flush();
    long long res = 0;
    cin >> res;
    return res;
}

int bit_size(long long x) {
    int cnt = 0;
    while (x > 0) {
        x >>= 1;
        cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        int cnt = bit_size(n) - 1;
        for (long long i = 1LL << cnt; i > 0; i >>= 1) {
            long long res = query(a | i, a | (i * 2 - 1));
            if (res != 0) { a |= i; }
        }
        for (long long i = 1LL << cnt; i > 0; i >>= 1) {
            long long res = query(b | i, b | (i * 2 - 1));
            if ((b | i) <= a && a <= (b | (i * 2 - 1))) { res ^= a; }
            if (res != 0) { b |= i; }
        }
        c = query(1, n) ^ a ^ b;
        cout << "ans " << a << " " << b << " " << c << endl;
        a = 0, b = 0, c = 0;
    }
    return 0;
}
