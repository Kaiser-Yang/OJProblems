// problem statement: https://www.luogu.com.cn/problem/P2613

#include <bits/stdc++.h>

constexpr long long MOD = 19260817;

using namespace std;

long long a, b;

long long read() {
    long long x = 0, f = 1;
    char ch = 0;
    do {
        ch = getchar();
        if (ch == '-') { f = -1; }
    } while (ch < '0' || ch > '9');
    do {
        x = (x * 10 % MOD + ch - '0') % MOD;
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return x * f;
}

long long ex_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long g = ex_gcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - a / b * y;
    return g;
}

int main() {
    a = read(), b = read();
    long long c = 0, k = 0;
    long long gcd = ex_gcd(b, MOD, c, k);
    if (gcd == 1) {
        c = (c % MOD + MOD) % MOD;
        cout << a * c % MOD << endl;
    } else {
        cout << "Angry!" << endl;
    }
    return 0;
}
