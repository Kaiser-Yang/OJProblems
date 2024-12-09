// problem statement: https://codeforces.com/contest/2040/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        int now = 1, ans = 1;
        while (now < n) {
            now = (now + 1) * 2;
            ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}
