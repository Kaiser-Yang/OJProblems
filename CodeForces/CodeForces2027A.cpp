// problem statement: https://codeforces.com/contest/2027/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n, w, h;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        int max_w = 0, max_h = 0;
        for (int i = 0; i < n; i++) {
            cin >> w >> h;
            max_w = max(max_w, w);
            max_h = max(max_h, h);
        }
        cout << 2 * (max_w + max_h) << '\n';
    }
    return 0;
}
