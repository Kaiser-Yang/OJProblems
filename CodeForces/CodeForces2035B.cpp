// problem statement: https://codeforces.com/contest/2035/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        if (n % 2 == 0) {
            for (int i = 0; i < n - 2; i++) {
                cout << '3';
            }
            cout << "66\n";
        } else {
            if (n == 1 || n == 3) { cout << "-1\n"; }
            else {
                for (int i = 0; i < n - 4; i++) {
                    cout << '3';
                }
                cout << "6366\n";
            }
        }
    }
    return 0;
}
