// problem statement: https://codeforces.com/problemset/problem/2029/A

#include <bits/stdc++.h>

using namespace std;

int T, l, r, k;

int main() {
    cin >> T;
    while (T--) {
        cin >> l >> r >> k;
        cout << max(0, r / k - l + 1) << '\n';
    }
    return 0;
}
