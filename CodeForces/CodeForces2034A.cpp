// problem statement: https://codeforces.com/contest/2034/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, a, b;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> a >> b;
        for (int m = min(a, b);; m++) {
            if (m % a == m % b) {
                cout << m << '\n';
                break;
            }
        }
    }
    return 0;
}
