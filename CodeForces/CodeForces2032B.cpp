// problem statement: https://codeforces.com/contest/2032/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        if ((k == 1 && n != 1) || (k != 1 && k == n)) {
            cout << -1 << '\n';
            continue;
        }
        if (k - 1 <= n - k) {
            cout << 2 * (k - 1) + 1 << "\n";
            for (int i = 1; i <= k; i++) { cout << i << " "; }
            for (int i = 1; i <= k - 1; i++) { cout << i + k << (i == k - 1 ? "\n" : " "); }
        } else {
            cout << 2 * (n - k) + 1 << '\n';
            for (int i = 1; i <= n - k; i++) { cout << i << " "; }
            for (int i = k; i <= n; i++) { cout << i << (i == n ? "\n" : " "); }
        }
    }
    return 0;
}
