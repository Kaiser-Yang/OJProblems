// problem statement: https://codeforces.com/problemset/problem/2028/B

#include <bits/stdc++.h>

using namespace std;

int T;
long long n, b, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> b >> c;
        if (b == 0 && c == 0) {
            if (n == 1) {
                cout << "0\n";
            } else if (n == 2) {
                cout << "1\n";
            } else {
                cout << "-1\n";
            }
        } else if (b == 0) {
            if (c == n - 1) {
                cout << n - 1 << '\n';
            } else if (c > n - 1) {
                cout << n << '\n';
            } else if (c == n - 2) {
                cout << n - 1 << '\n';
            } else {
                cout << "-1\n";
            }
        } else {
            if (c > n - 1) {
                cout << n << '\n';
            } else {
                cout << n - ((n - 1 - c) / b + 1) << '\n';
            }
        }
    }
    return 0;
}
