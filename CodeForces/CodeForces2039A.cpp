// problem statement: https://codeforces.com/contest/2039/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << i * 2 + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
