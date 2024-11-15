// problem statement: https://codeforces.com/contest/2031/problem/B

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

int T, n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) { cin >> a[i]; }
        bool ok = true;
        for (int i = 1; i < n; i++) {
            if (a[i] == i) { continue; }
            if (abs(a[i + 1] - a[i]) != 1) {
                ok = false;
                break;
            }
            swap(a[i], a[i + 1]);
            if (a[i] != i) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
