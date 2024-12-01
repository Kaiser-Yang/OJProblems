// problem statement: https://codeforces.com/contest/2034/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n, m, k;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k >> str;
        int cnt = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            if (str[i] == '0') {
                cnt++;
            } else {
                cnt = 0;
            }
            if (cnt == m) {
                ans++;
                i += k - 1;
                cnt = 0;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
