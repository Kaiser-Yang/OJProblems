// problem statement: https://codeforces.com/problemset/problem/1187/A

#include <bits/stdc++.h>

using namespace std;

int T, n, s, t;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> s >> t;
        if (s == n && t == n) {
            cout << "1\n";
        } else if (s + t == n) {
            cout << max(s, t) + 1 << '\n';
        } else {
            cout << n - min(s, t) + 1 << '\n';
        }
    }
    return 0;
}
