// problem statement: https://codeforces.com/problemset/problem/1236/A

#include <bits/stdc++.h>

using namespace std;

int T, a, b, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        int ans = 0;
        while (b > 0 && c >= 2) {
            ans += 3;
            b--;
            c -= 2;
        }
        while (a > 0 && b >= 2) {
            ans += 3;
            a--;
            b -= 2;
        }
        cout << ans << endl;
    }
    return 0;
}
