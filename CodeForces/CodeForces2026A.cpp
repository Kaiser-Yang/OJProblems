// problem statement: https://codeforces.com/contest/2026/problem/A

#include <bits/stdc++.h>

using namespace std;

int t, x, y, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> x >> y >> k;
        for (int a = 1; a <= x; a++) {
            int b = ceil(sqrt(k * k - a * a));
            if (a <= min(x, y) && b <= min(x, y)) {
                cout << "0 0 " << a << " " << b << "\n";
                cout << "0 " << a << " " << b << " 0\n";
                break;
            }
        }
    }
    return 0;
}
