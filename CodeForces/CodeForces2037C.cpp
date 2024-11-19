// problem statement: https://codeforces.com/problemset/problem/2037/C

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        if (n <= 4) {
            cout << "-1\n";
        } else if (n == 5) {
            cout << "1 3 5 4 2\n";
        } else if (n == 6) {
            cout << "1 3 5 4 2 6\n";
        }
        if (n >= 7) {
            for (int i = 1; i <= n; i += 2) {
                if (i == 7) { continue; }
                cout << i << " ";
            }
            cout << "7 ";
            for (int i = 2; i <= n; i += 2) { cout << i << " "; }
            cout << '\n';
        }
    }
    return 0;
}
