// problem statement: https://codeforces.com/contest/2035/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n, m, r, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> r >> c;
        cout << 1LL * (n - r) * (m - 1) + 1LL * (n - r) * m + m - c << '\n';
    }
    return 0;
}
