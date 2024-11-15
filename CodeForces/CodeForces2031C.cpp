// problem statement: https://codeforces.com/contest/2031/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        if (n % 2 == 1 && n <= 25) {
            cout << "-1\n";
            continue;
        }
        if (n % 2 == 1) {
            cout << "1 2 2 3 3 4 4 5 5 1 6 6 7 7 8 8 9 9 10 10 11 11 12 13 13 1 12";
            int now = 14;
            for (int i = 28; i <= n; i += 2) {
                cout << " " << now << " " << now;
                now++;
            }
            cout << '\n';
            continue;
        }
        for (int i = 1; i <= n / 2; i++) { cout << i << " " << i << (i == n / 2 ? '\n' : ' '); }
    }
    return 0;
}
